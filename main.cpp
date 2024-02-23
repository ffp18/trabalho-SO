#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <locale.h>

// Fun��es
int calcularNumeroDaPagina(int endereco, int tamanhoDaPagina) {
    return endereco / tamanhoDaPagina;
}

int calcularDeslocamento(int endereco, int tamanhoDaPagina) {
    return endereco % tamanhoDaPagina;
}

// Fun��o para perguntar ao usu�rio qual tamanho de pagina��o ele deseja
int escolherTamanhoDaPagina() {
    int tamanhoDaPagina;
    int opcao;
    std::cout << "\nQual o tamanho da pagina��o?\n1 - 256 bytes\n2 - 512 bytes\n3 - 1024\n4 - 2048\n5 - 4096\n\nDigite o n�mero da op��o desejada: ";
    std::cin >> opcao;

    if (opcao == 1) {
        tamanhoDaPagina = 256;
    } else if (opcao == 2) {
        tamanhoDaPagina = 512;
    } else if (opcao == 3) {
        tamanhoDaPagina = 1024;
    } else if (opcao == 4) {
        tamanhoDaPagina = 2048;
    } else if (opcao == 5) {
        tamanhoDaPagina = 4096;
    } else {
        std::cout << "Op��o inv�lida, o programa ser� encerrado.\n";
        exit(1);
    }

    return tamanhoDaPagina;
}

// Fun��o para gerar o arquivo data_memory.txt
void gerarArquivoDeDados() {
    srand(time(0));
    std::ofstream arquivoDeDados("data_memory.txt");

    for(int i=0; i<1000000; i++) {
        int numero = rand() % 101;
        arquivoDeDados << numero << "\n";
    }

    arquivoDeDados.close();
}

// Main
int main() {
    setlocale(LC_ALL, "Portuguese");

    // Gera o arquivo data_memory.txt
    gerarArquivoDeDados();

    // Vari�veis
    int numeroDaPagina = 0;
    int deslocamento = 0;
    int endereco = 0;
    int valor = 0;

    // Perguntar ao usu�rio qual op��o ele deseja
    int opcao;
    std::cout << "Deseja ler os endere�os de um arquivo ou digitar um endere�o?\n1 - Digitar endere�o\n2 - Ler arquivo\n\nDigite o n�mero da op��o desejada: ";
    std::cin >> opcao;

    if (opcao == 1) {
        std::cout << "Digite o endere�o: ";
        std::cin >> endereco;

        if (endereco < 0) {
            std::cout << "Endere�o inv�lido.\n";
            return 1;
        }

        int tamanhoDaPagina = escolherTamanhoDaPagina();

        numeroDaPagina = calcularNumeroDaPagina(endereco, tamanhoDaPagina);
        deslocamento = calcularDeslocamento(endereco, tamanhoDaPagina);

        std::ifstream arquivoDeDados("data_memory.txt");
        std::string linhaDeDados;

        for(int i=0; i<=deslocamento; i++) {
            getline(arquivoDeDados, linhaDeDados);
        }

        valor = std::stoi(linhaDeDados);
        arquivoDeDados.close();

        // Imprime os resultados diretamente no console
        std::cout << "\nO endere�o " << endereco << " cont�m:\n\tn�mero da p�gina = " << numeroDaPagina << "\n\tdeslocamento = " << deslocamento << "\n\tValor lido: " << valor << "\n\n";

        return 0; // Encerra o programa ap�s imprimir os resultados

    } else if (opcao == 2) {
        std::string nomeDoArquivo;
        std::cout << "Digite o nome do arquivo: ";
        std::cin >> nomeDoArquivo;

        std::ifstream arquivo(nomeDoArquivo);
        if (!arquivo) {
            std::cout << "Erro ao abrir o arquivo.\n";
            return 1;
        }

        int tamanhoDaPagina = escolherTamanhoDaPagina();

        while (arquivo >> endereco) {
            numeroDaPagina = calcularNumeroDaPagina(endereco, tamanhoDaPagina);
            deslocamento = calcularDeslocamento(endereco, tamanhoDaPagina);

            std::ifstream arquivoDeDados("data_memory.txt");
            std::string linhaDeDados;

            for(int i=0; i<=deslocamento; i++) {
                getline(arquivoDeDados, linhaDeDados);
            }

            valor = std::stoi(linhaDeDados);
            arquivoDeDados.close();

            // Imprime os resultados diretamente no console
            std::cout << "\nO endere�o " << endereco << " cont�m:\n\tn�mero da p�gina = " << numeroDaPagina << "\n\tdeslocamento = " << deslocamento << "\n\tValor lido: " << valor << "\n\n";

            break; // Encerra a leitura ap�s imprimir o resultado do primeiro endere�o no arquivo
        }

        return 0; // Encerra o programa ap�s imprimir todos os resultados

    } else {
        std::cout << "Op��o inv�lida, o programa ser� encerrado.\n";
        return 1;
    }

    return 0;
}


