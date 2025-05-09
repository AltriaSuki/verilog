#include"../include/rtlil_to_dot.h"

RTLILToDot::RTLILToDot(Lexer& lexer)
{
    //获取一组tokens
    Token token = lexer.NextToken();
    while (token.type != END_OF_INPUT) {
        tokens.push_back(token);
        token = lexer.NextToken();
    }
    tokens.push_back(token);//push back the END_OF_INPUT token
    currentTokenIndex = 0;
    currentToken = tokens[currentTokenIndex];

    //for (auto& i : tokens)
    //{
    //    std::cout << i.value << std::endl;
    //}
}




//TO DO 修改以匹配RTLIL格式文件
void RTLILToDot::read_file()
{
    while (currentToken.type!=END_OF_INPUT)
    {
        gen_module();
        //解析完模组，解析下一个
        currentToken = tokens[++currentTokenIndex];
        ++moduleID;
    }
 
}
void RTLILToDot::gen_module()
{
    while(currentToken.value!="endmodule")
    {
        if (currentToken.value == "input") {
            gen_input();
            currentToken = tokens[++currentTokenIndex];
        }
        else if (currentToken.value == "output") {
            gen_output();
            currentToken = tokens[++currentTokenIndex];
        }
        else if (currentToken.value == "cell") {

            inCell = true;
            gen_cell();
            currentToken = tokens[++currentTokenIndex];
            inCell = false;
        }
        else if (currentToken.value == "connect") {
            if (!inCell)
                gen_connection();
            currentToken = tokens[++currentTokenIndex];
        }
        else
        {
            currentToken = tokens[++currentTokenIndex];
        }
    }

}

void RTLILToDot::gen_input()
{
    //should be name
    currentToken = tokens[currentTokenIndex + 3];
    inputs.push_back(currentToken.value + "_" + std::to_string(moduleID));
}

void RTLILToDot::gen_output()
{
    //should be name
    currentToken = tokens[currentTokenIndex + 3];
    outputs.push_back(currentToken.value + "_" + std::to_string(moduleID));
}

void RTLILToDot::gen_cell()
{
    
    //should be type,get type
    currentToken = tokens[++currentTokenIndex];
    if(currentToken.value!="$mux$")
    {
        Cell* cell = new Cell();
        cell->type = currentToken.value + "_" + std::to_string(moduleID);

        currentToken = tokens[++currentTokenIndex];
        cell->name = currentToken.value + "_" + std::to_string(moduleID);

        //输入
        currentTokenIndex = currentTokenIndex + 3;
        currentToken = tokens[currentTokenIndex];
        cell->ports["A"] = currentToken.value + "_" + std::to_string(moduleID);

        currentTokenIndex = currentTokenIndex + 3;
        currentToken = tokens[currentTokenIndex];
        cell->ports["B"] = currentToken.value + "_" + std::to_string(moduleID);
        //输出
        currentTokenIndex = currentTokenIndex + 3;
        currentToken = tokens[currentTokenIndex];
        cell->ports["Y"] = currentToken.value + "_" + std::to_string(moduleID);

        cells.push_back(cell);
    }
    else
    {
        Cell* cell = new Cell();
        cell->type = currentToken.value + "_" + std::to_string(moduleID);

        currentToken = tokens[++currentTokenIndex];
        cell->name = currentToken.value + "_" + std::to_string(moduleID);

        //输入
        currentTokenIndex = currentTokenIndex + 3;
        currentToken = tokens[currentTokenIndex];
        cell->ports["A"] = currentToken.value + "_" + std::to_string(moduleID);

        currentTokenIndex = currentTokenIndex + 3;
        currentToken = tokens[currentTokenIndex];
        cell->ports["B"] = currentToken.value + "_" + std::to_string(moduleID);

        currentTokenIndex = currentTokenIndex + 3;
        currentToken = tokens[currentTokenIndex];
        cell->ports["S"] = currentToken.value + "_" + std::to_string(moduleID);
        //输出
        currentTokenIndex = currentTokenIndex + 3;
        currentToken = tokens[currentTokenIndex];
        cell->ports["Y"] = currentToken.value + "_" + std::to_string(moduleID);

        cells.push_back(cell);
    }
}

void RTLILToDot::gen_connection()
{
    currentToken = tokens[++currentTokenIndex];
    Connection* connection = new Connection();
    connection->dst = currentToken.value + "_" + std::to_string(moduleID);

    currentToken = tokens[++currentTokenIndex];
    connection->src = currentToken.value + "_" + std::to_string(moduleID);

    connection->label = "=";

    connections.push_back(connection);
}

void RTLILToDot::Generate_DOT()
{
    std::ofstream dotFile("output.txt");
    dotFile << "digraph G {\n";
    dotFile << "  rankdir=LR;\n";
    dotFile << "  node [shape=box, style=rounded];\n";

    // 输入输出节点
    for (auto& in : inputs)
        dotFile << "  \"" << in << "\" [shape=ellipse, color=blue];\n";
    for (auto& out : outputs)
        dotFile << "  \"" << out << "\" [shape=doublecircle, color=green];\n";

    // 单元节点
    for (auto& cell : cells)
    {
        std::ostringstream oss;
        oss << "\"" << cell->name << "\" [\n";
        oss << "  label=\"{ {";

        std::vector<std::string> inputs, outputs;
        for (const auto& [port, signal] : cell->ports) {
            if (port == "Y") {
                outputs.push_back("<" + port + "> " + port);
            }
            else {
                inputs.push_back("<" + port + "> " + port);
            }
        }

        for (size_t i = 0; i < inputs.size(); ++i) {
            oss << inputs[i];
            if (i + 1 < inputs.size()) oss << " | ";
        }

        oss << "} | " << cell->type << " | {";

        for (size_t i = 0; i < outputs.size(); ++i) {
            oss << outputs[i];
            if (i + 1 < outputs.size()) oss << " | ";
        }

        oss << "} }\",\n";
        oss << "  shape=record,\n";
        oss << "  style=filled,\n";
        oss << "  fillcolor=lightblue\n";
        oss << "];\n";

        dotFile << oss.str();
        dotFile << "  \"" << cell->ports["A"] << "\" -> \"" << cell->name << "\":A ;\n";
        dotFile << "  \"" << cell->ports["B"] << "\" -> \"" << cell->name << "\":B ;\n";
        dotFile << "  \"" << cell->name << "\":Y -> \"" << cell->ports["Y"] << "\" ;\n";
        if ((cell->ports.contains("S")))
            dotFile << "  \"" << cell->ports["S"] << "\" -> \"" << cell->name << "\":S ;\n";
    }

    // 连接
    for (auto& conn : connections)
        dotFile << "  \"" << conn->src << "\" -> \"" << conn->dst << "\" [label=\"" << conn->label << "\"];\n";

    dotFile << "}\n";

    dotFile.close();

    std::cout << "DOT 文件已生成: carry.dot\n";


}
