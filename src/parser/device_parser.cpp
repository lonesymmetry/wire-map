#include "parser/device_parser.hpp"

#include "parser/util.hpp"
#include "util.hpp"

#include <string_view>

namespace wiremap::parser{

    std::string parseDeviceName(const std::vector<std::string>& LINE){
        if(LINE.size() == 2 && LINE[DeviceNode::KEYWORD_POS] == DeviceNode::KEYWORD){
            return {LINE[1]};
        }
        assert(0);
    }

    DeviceNode DeviceNode::parse(const std::vector<std::string>& IN){
        assert(!IN.empty());

        constexpr unsigned DEVICE_START_LINE = 0;

        DeviceNode device_node;
        device_node.name = parseDeviceName(splitLine(IN[DEVICE_START_LINE]));

        for(unsigned i = DEVICE_START_LINE + 1; i < IN.size(); i++){
            unsigned indent_count = indentCount(IN[i]);
            if(indent_count != 1 && !IN[i].empty()){
                if(indent_count == 0){ //end of device definition
                    break;
                }
                continue;
            }
            std::vector<std::string> split_line = splitLine(IN[i]);
            if(!split_line.empty()){
                if(split_line.front() == ParameterNode::KEYWORD){
                    device_node.parameters.push_back(ParameterNode::parse(split_line));
                } else if(split_line.front() == ConstantNode::KEYWORD){
                    device_node.constants.push_back(ConstantNode::parse(split_line));
                } else if(split_line.front() == ResultNode::KEYWORD){
                } else {
                    NYI
                }
            }
        }
        return device_node;
    }

    std::string DeviceNode::toString()const{
        std::string a = "{";
        a += "\"name\":\"" + name + "\", ";
        a += "\"parameters\":" + asString(parameters, &ParameterNode::toString) + ", ";
        a += "\"constants\":" + asString(constants, &ConstantNode::toString) + ", ";
        a += "\"results\":" + asString(results, &ResultNode::toString);
        a += "}";
        return a;
    }
}
