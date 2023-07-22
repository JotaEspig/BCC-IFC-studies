/*
Código morse. O código morse é um esquema de codificação de letras e números utilizando
pontos e traços. Neste exercício você deve escrever um programa que usa um dicionário para
armazenar o mapeamento de letras e números para código Morse. Voce deve representar os
pontos com símbolo de ponto “.” e traços com sinal de subtração “-“. A tabela abaixo mostra o
mapeamento de letras e números para código Morse. Seu programa deve ler uma mensagem
do usuário e então deve traduzir cada letra e número para código Morse, deixando um espaço
em branco entra cada caractere traduzido. O programa deve ignorar qualquer caracter que
não seja letra ou número. Por exemplo, a mensagem Hello, World! Deve ser exibida da
seguinte forma: .... . .-.. .-.. --- .-- --- .-. .-.. -..
*/

#include <iostream>
#include <string>
#include <map>

std::string translate_to_morse(const std::string &message) {
    std::map<char, std::string> dictionary = {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."}, {'F', "..-."},
        {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
        {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},
        {'S', "..."}, {'T', "-"}, {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
        {'Y', "-.--"}, {'Z', "--.."},
        {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
        {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."},
    };

    std::string morse_code;
    for (char c : message) {
        c = std::toupper(c);

        auto it = dictionary.find(c);
        if (it != dictionary.end()) {
            morse_code += it->second;
            morse_code += " ";
        }
    }

    return morse_code;
}

int main()
{
    std::string message;
    std::cout << "Enter a message: ";
    std::getline(std::cin, message);

    std::string morse_code = translate_to_morse(message);

    std::cout << "Morse Code: " << morse_code << std::endl;

    return 0;
}
