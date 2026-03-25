#include <stdio.h>
#include <stdlib.h>
#include <string.h>




// Definição da estrutura do funcionário
typedef struct {
    int matricula;
    char nome[100];
    char cargo[50];
    float salario;
} Funcionario;


// Definição da estrutura TreeNode
typedef struct TreeNode {
    struct TreeNode *leftPtr;
    Funcionario funcionario;
    struct TreeNode *rightPtr;
} TreeNode;

typedef TreeNode *TreeNodePtr;



// ====== PROTÓTIPOS DAS FUNÇÕES ====================

void insertNode(TreeNodePtr *treePtr, Funcionario funcionario);
TreeNodePtr searchNode(TreeNodePtr treePtr, int matricula);
void updateFuncionario(TreeNodePtr treePtr, int matricula);
void inOrder(TreeNodePtr treePtr);
void freeTree(TreeNodePtr treePtr);
void limparBuffer();

// ============== IMPLEMENTAÇÃO DAS FUNÇÕES ====================

//função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para inserir nó na árvore (ordenação por matrícula  )
void insertNode(TreeNodePtr *treePtr, Funcionario funcionario) {
	
    // Se arvore estiver vazia
    if (*treePtr == NULL) {
        *treePtr = (TreeNodePtr)malloc(sizeof(TreeNode));

        // Se a memória foi alocada, atribui dados
        if (*treePtr != NULL) {
            (*treePtr)->funcionario = funcionario;
            (*treePtr)->leftPtr = NULL;
            (*treePtr)->rightPtr = NULL;
        } 
        else {
            printf("Funcionário não inserido. Não há memória disponível.\n");
        }
    } 
    else { // Árvore não está vazia
        // Comparação das matrículas  - a lógica de adicionar na arvore lado direito, ou esquerdo os valores
        if (funcionario.matricula < (*treePtr)->funcionario.matricula) {
            insertNode(&((*treePtr)->leftPtr), funcionario);
        } 
        else if (funcionario.matricula > (*treePtr)->funcionario.matricula) {
            insertNode(&((*treePtr)->rightPtr), funcionario);
        } 
        else { // Matrícula duplicada - não insere
            printf("Funcionário com matrícula %d já existe no sistema!\n", funcionario.matricula);
        }	
    } 
}

// Função para buscar funcionário por matrícula
TreeNodePtr searchNode(TreeNodePtr treePtr, int matricula) {
    if (treePtr == NULL) {
        return NULL;
    }
    
    
    if (matricula == treePtr->funcionario.matricula) {
        return treePtr;
    }
    else if (matricula < treePtr->funcionario.matricula) {
        return searchNode(treePtr->leftPtr, matricula);
    }
    else {
        return searchNode(treePtr->rightPtr, matricula);
    }
}

// Função para atualizar os dados do funcionário
void updateFuncionario(TreeNodePtr treePtr, int matricula) {
    TreeNodePtr funcEncontrado = searchNode(treePtr, matricula);
    
    
    if (funcEncontrado != NULL) {
        printf("\n=== Atualizando dados do funcionário ===\n");
        printf("Matrícula: %d\n", funcEncontrado->funcionario.matricula);
        
        printf("Nome atual: %s\n", funcEncontrado->funcionario.nome);         
        printf("Novo nome: ");
        fgets(funcEncontrado->funcionario.nome, 100, stdin);
        funcEncontrado->funcionario.nome[strcspn(funcEncontrado->funcionario.nome, "\n")] = '\0';     //     Exemplo: strcspn("hello world", "o") retorna 4 (o 'o' é encontrado na posição 4, então ela lê "hell").
        
        printf("Cargo atual: %s\n", funcEncontrado->funcionario.cargo);
        printf("Novo cargo: ");
        fgets(funcEncontrado->funcionario.cargo, 50, stdin);
        funcEncontrado->funcionario.cargo[strcspn(funcEncontrado->funcionario.cargo, "\n")] = '\0';
        
        
        printf("Salário atual: R$ %.2f\n", funcEncontrado->funcionario.salario);
        printf("Novo salário: R$ ");
        scanf("%f", &funcEncontrado->funcionario.salario);
        
        printf("Dados atualizados com sucesso!\n");
    }
    else {
        printf("Funcionário com matrícula %d não encontrado!\n", matricula);
    }
}

// Percorrimento em ordem - ordem crescente por matricula
void inOrder(TreeNodePtr treePtr) {
	
    // Se árvore não está vazia, percorre
    if (treePtr != NULL) {
        inOrder(treePtr->leftPtr);
        printf("\n--- Funcionário ---\n");
        printf("Matrícula: %d\n", treePtr->funcionario.matricula);
        printf("Nome: %s\n", treePtr->funcionario.nome);
        printf("Cargo: %s\n", treePtr->funcionario.cargo);
        printf("Salário: R$ %.2f\n", treePtr->funcionario.salario);
        printf("-------------------\n");
        
        inOrder(treePtr->rightPtr);
    }
}

// Função para liberar a memória da árvore
void freeTree(TreeNodePtr treePtr) {
    if (treePtr != NULL) {
        freeTree(treePtr->leftPtr);
        freeTree(treePtr->rightPtr);
        free(treePtr);
    }
}

// Função para inserir novo funcionário 
void inserirFuncionario(TreeNodePtr *rootPtr) {
    Funcionario novoFuncionario;
    
    printf("\n=== Inserir Novo Funcionário ===\n");
    
    printf("Matrícula: ");
    scanf("%d", &novoFuncionario.matricula);
    limparBuffer();
    
    // Verifica se a matrícula já existe
    if (searchNode(*rootPtr, novoFuncionario.matricula) != NULL) {
        printf("Erro: Matrícula %d já cadastrada!\n", novoFuncionario.matricula);
        return;
	}
    
    printf("Nome: ");
    fgets(novoFuncionario.nome, 100, stdin);
    novoFuncionario.nome[strcspn(novoFuncionario.nome, "\n")] = '\0';
    
    printf("Cargo: ");
    fgets(novoFuncionario.cargo, 50, stdin);
    novoFuncionario.cargo[strcspn(novoFuncionario.cargo, "\n")] = '\0';
    
    printf("Salário: R$ ");
    scanf("%f", &novoFuncionario.salario);
    limparBuffer();
    
    insertNode(rootPtr, novoFuncionario);
    printf("Funcionário inserido com sucesso!\n");
}




// Função para buscar funcionário (interface com usuário)
void buscarFuncionario(TreeNodePtr rootPtr) {
    int matricula;
    TreeNodePtr funcEncontrado;
    
    printf("\n=== Buscar Funcionário ===\n");
    printf("Digite a matrícula: ");
    scanf("%d", &matricula);
    limparBuffer();
    
    funcEncontrado = searchNode(rootPtr, matricula);
    
    if (funcEncontrado != NULL) {
        printf("\n--- Funcionário Encontrado ---\n");
        printf("Matrícula: %d\n", funcEncontrado->funcionario.matricula);
        printf("Nome: %s\n", funcEncontrado->funcionario.nome);
        printf("Cargo: %s\n", funcEncontrado->funcionario.cargo);
        printf("Salário: R$ %.2f\n", funcEncontrado->funcionario.salario);
        printf("-----------------------------\n");
    }
    else {
        printf("Funcionário com matrícula %d não encontrado!\n", matricula);
    }
}



//Função para listar todos os funcionários 
void listarFuncionarios(TreeNodePtr rootPtr) {
    printf("\n=== Lista de Funcionários (Ordem Crescente por Matrícula) ===\n");
    if (rootPtr == NULL) {
        printf("Nenhum funcionário cadastrado.\n");
    }
    else {
        inOrder(rootPtr);
    }
}




int main() {
    TreeNodePtr rootPtr = NULL;
    int opcao;
    
    int matricula;
    
    do {
        printf("\n=== SISTEMA DE CADASTRO DE FUNCIONÁRIOS ===\n");
        printf("1 - Inserir novo funcionário\n");
        printf("2 - Buscar funcionário\n");
        printf("3 - Atualizar dados do funcionário\n");
        printf("4 - Listar todos os funcionários\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        
        switch(opcao) {
            case 1:
                inserirFuncionario(&rootPtr);
                break;
            case 2:
                buscarFuncionario(rootPtr);
                break;
            case 3:
                printf("\n=== Atualizar Funcionário ===\n");
                printf("Digite a matrícula do funcionário: ");
                scanf("%d", &matricula);
                limparBuffer();
                updateFuncionario(rootPtr, matricula);
                break;
            case 4:
                listarFuncionarios(rootPtr);
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    }   while(opcao != 0);
    

    freeTree(rootPtr);
    
    return 0;
}
