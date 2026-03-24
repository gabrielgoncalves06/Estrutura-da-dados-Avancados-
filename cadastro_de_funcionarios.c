#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Funcionario {
    int matricula;              
    char nome[100];             
    char cargo[50];             
    float salario;              
    struct Funcionario* left;   
    struct Funcionario* right;  
} Funcionario;

// Função para criar um novo nó
Funcionario* criarFuncionario(int matricula, char nome[], char cargo[], float salario) {
    Funcionario* novo = (Funcionario*)malloc(sizeof(Funcionario));
    
    novo->matricula = matricula;
    strcpy(novo->nome, nome);
    strcpy(novo->cargo, cargo);
    novo->salario = salario;
    novo->left = NULL;
    novo->right = NULL;
    
    return novo;
}


Funcionario* inserirFuncionario(Funcionario* raiz, int matricula, char nome[], char cargo[], float salario) {
     
    if (raiz == NULL) {
        return criarFuncionario(matricula, nome, cargo, salario);
    }
    
    //se a matrícula já existe, não insere
    if (matricula == raiz->matricula) {
        printf("Erro: Matrícula %d já cadastrada!\n", matricula);
        return raiz;
    }
    
    // inserção na subárvore esquerda (matrícula menor)
    if (matricula < raiz->matricula) {
        raiz->left = inserirFuncionario(raiz->left, matricula, nome, cargo, salario);
    } 
    // inserção na subárvore direita (matrícula maior)
    else if (matricula > raiz->matricula) {
        raiz->right = inserirFuncionario(raiz->right, matricula, nome, cargo, salario);
    }
    
    return raiz;
}

// função para buscar um funcionário pela matrícula
Funcionario* buscarFuncionario(Funcionario* raiz, int matricula) {
    
    if (raiz == NULL) {
        return NULL;
    }
    
    // encontrou a matrícula
    if (matricula == raiz->matricula) {
        return raiz;
    }
    
   
    if (matricula < raiz->matricula) {
        return buscarFuncionario(raiz->left, matricula);
    }
   
    else {
        return buscarFuncionario(raiz->right, matricula);
    }
}

// função para encontrar o nó com menor valor (sucessor)
Funcionario* encontrarMinimo(Funcionario* raiz) {
    Funcionario* atual = raiz;
    
    //Percorre a subárvore esquerda até encontrar o menor
    while (atual && atual->left != NULL) {
        atual = atual->left;
    }
    return atual;
}

//Função para remover um funcionário da árvore
Funcionario* removerFuncionario(Funcionario* raiz, int matricula) {
    // árvore vazia ou nó não encontrado
    if (raiz == NULL) {
        printf("Funcionário com matrícula %d não encontrado!\n", matricula);
        return NULL;
    }
    
    // Caso 1: matrícula menor, busca na subárvore esquerda
    if (matricula < raiz->matricula) {
        raiz->left = removerFuncionario(raiz->left, matricula);
    }
    // Caso 2: matrícula maior, busca na subárvore direita
    else if (matricula > raiz->matricula) {
        raiz->right = removerFuncionario(raiz->right, matricula);
    }
    // Caso 3: encontrou o nó a ser removido
    else {
        // Caso 3.1: nó com um ou nenhum filho
        if (raiz->left == NULL) {
            Funcionario* temp = raiz->right;
            free(raiz);
            printf("Funcionário removido com sucesso!\n");
            return temp;
        }
        else if (raiz->right == NULL) {
            Funcionario* temp = raiz->left;
            free(raiz);
            printf("Funcionário removido com sucesso!\n");
            return temp;
        }
        
        // Caso 3.2: nó com dois filhos
        // Encontra o sucessor (menor valor da subárvore direita)
        Funcionario* temp = encontrarMinimo(raiz->right);
        
        // Copia os dados do sucessor para o nó atual
        raiz->matricula = temp->matricula;
        strcpy(raiz->nome, temp->nome);
        strcpy(raiz->cargo, temp->cargo);
        raiz->salario = temp->salario;
        
        // Remove o sucessor da subárvore direita
        raiz->right = removerFuncionario(raiz->right, temp->matricula);
    }
    
    return raiz;
}


void atualizarFuncionario(Funcionario* raiz, int matricula) {
    Funcionario* funcionario = buscarFuncionario(raiz, matricula);
    
    if (funcionario == NULL) {
        printf("Funcionário com matrícula %d não encontrado!\n", matricula);
        return;
    }
    
    printf("\n=== Atualizando dados do funcionário ===\n");
    printf("Matrícula: %d\n", funcionario->matricula);
    printf("Nome atual: %s\n", funcionario->nome);
    printf("Novo nome: ");
    getchar();  
    fgets(funcionario->nome, 100, stdin);
    funcionario->nome[strcspn(funcionario->nome, "\n")] = '\0';
    
    printf("Cargo atual: %s\n", funcionario->cargo);
    printf("Novo cargo: ");
    fgets(funcionario->cargo, 50, stdin);
    funcionario->cargo[strcspn(funcionario->cargo, "\n")] = '\0';
    
    printf("Salário atual: %.2f\n", funcionario->salario);
    printf("Novo salário: ");
    scanf("%f", &funcionario->salario);
    
    printf("Dados atualizados com sucesso!\n");
}


void exibirFuncionario(Funcionario* funcionario) {
    printf("Matrícula: %d\n", funcionario->matricula);
    printf("Nome: %s\n", funcionario->nome);
    printf("Cargo: %s\n", funcionario->cargo);
    printf("Salário: R$ %.2f\n", funcionario->salario);
    printf("------------------------\n");
}

// Função para listar todos os funcionários em ordem crescente de matrícula
void listarFuncionarios(Funcionario* raiz) {
    if (raiz != NULL) {
        // Percorre a subárvore esquerda (matrículas menores)
        listarFuncionarios(raiz->left);
        
        // Exibe o nó atual
        exibirFuncionario(raiz);
        
        // Percorre a subárvore direita (matrículas maiores)
        listarFuncionarios(raiz->right);
    }
}

// Função para liberar a memória da árvore
void liberarArvore(Funcionario* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->left);
        liberarArvore(raiz->right);
        free(raiz);
    }
}


void exibirMenu() {
    printf("\n=== SISTEMA DE CADASTRO DE FUNCIONÁRIOS ===\n");
    printf("1 - Inserir funcionário\n");
    printf("2 - Buscar funcionário\n");
    printf("3 - Atualizar funcionário\n");
    printf("4 - Remover funcionário\n");
    printf("5 - Listar todos os funcionários\n");
    printf("6 - Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    Funcionario* raiz = NULL;
    int opcao, matricula;
    char nome[100], cargo[50];
    float salario;
    
    do {
        exibirMenu();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: 
                printf("\n=== Inserir novo funcionário ===\n");
                printf("Matrícula: ");
                scanf("%d", &matricula);
                
               
                if (buscarFuncionario(raiz, matricula) != NULL) {
                    printf("Erro: Matrícula %d já cadastrada!\n", matricula);
                    break;
                }
                
                getchar();  
                printf("Nome: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                
                printf("Cargo: ");
                fgets(cargo, 50, stdin);
                cargo[strcspn(cargo, "\n")] = '\0';
                
                printf("Salário: ");
                scanf("%f", &salario);
                
                raiz = inserirFuncionario(raiz, matricula, nome, cargo, salario);
                printf("Funcionário inserido com sucesso!\n");
                break;
                
            case 2:
                printf("\n=== Buscar funcionário ===\n");
                printf("Matrícula: ");
                scanf("%d", &matricula);
                
                Funcionario* encontrado = buscarFuncionario(raiz, matricula);
                if (encontrado != NULL) {
                    printf("\nFuncionário encontrado:\n");
                    exibirFuncionario(encontrado);
                } else {
                    printf("Funcionário com matrícula %d não encontrado!\n", matricula);
                }
                break;
                
            case 3: 
                printf("\n=== Atualizar funcionário ===\n");
                printf("Matrícula do funcionário a ser atualizado: ");
                scanf("%d", &matricula);
                atualizarFuncionario(raiz, matricula);
                break;
                
            case 4: 
                printf("\n=== Remover funcionário ===\n");
                printf("Matrícula do funcionário a ser removido: ");
                scanf("%d", &matricula);
                raiz = removerFuncionario(raiz, matricula);
                break;
                
            case 5: 
                printf("\n=== Lista de Funcionários (ordem crescente por matrícula) ===\n");
                if (raiz == NULL) {
                    printf("Nenhum funcionário cadastrado.\n");
                } else {
                    listarFuncionarios(raiz);
                }
                break;
                
            case 6: 
                printf("\nEncerrando o sistema...\n");
                liberarArvore(raiz);
                break;
                
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 6);
    
    return 0;
}
