#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// !AVISO!
// USUARIO: teste
// SENHA: teste1234

typedef struct {
    char nomeCliente[80];
    char tamanho[80];
    int numAdicionais;
    float preco;
} Acai;

float calcularPreco(char* tamanho, int numAdicionais) {
    float precoBase = 0;
    if(strstr(tamanho, "300")) precoBase = 10.0;
    else if(strstr(tamanho, "500")) precoBase = 14.0;
    else if(strstr(tamanho, "700")) precoBase = 18.0;
    else precoBase = 12.0;
    return precoBase + (numAdicionais * 1.50);
}

void imprimirDetalhesPedido(Acai p) {
    printf("----------------------------------------\n");
    printf("Cliente: %s\n", p.nomeCliente);
    printf("Tamanho: %s\n", p.tamanho);
    printf("Adicionais: %d\n", p.numAdicionais);
    printf("Preco: R$ %.2f\n", p.preco);
}

int realizarLoginComEmail();
void exibirMenuPrincipal();
void registrarPedido();
void listarPedidos();
void editarPedido();
void excluirPedido();
void calcularFaturamentoTotal();
void buscarPedidoPorCliente();
void listarPedidosPorTamanho();
void listarPedidosComMaisDeNAdicionais();
void listarPedidosAcimaDeValor();
void limparBuffer();

int main() {
    while (realizarLoginComEmail() != 1) {
        printf("\nTente novamente.\n");
    }
  

    int opcaoPrincipal;
    do {
        exibirMenuPrincipal();
        printf("Opcao: ");
        scanf("%d", &opcaoPrincipal);
        limparBuffer();

        switch (opcaoPrincipal) {
            case 1: registrarPedido(); break;
            case 2: listarPedidos(); break;
            case 3: editarPedido(); break;
            case 4: excluirPedido(); break;
            case 5: calcularFaturamentoTotal(); break;
            case 6: buscarPedidoPorCliente(); break;
            case 7: listarPedidosPorTamanho(); break;
            case 8: listarPedidosComMaisDeNAdicionais(); break;
            case 9: listarPedidosAcimaDeValor(); break;
            case 0: break;
            default: printf("\nOpcao invalida.\n"); break;
        }
    } while (opcaoPrincipal != 0);

    printf("\nSistema encerrado.\n");
    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int realizarLoginComEmail() {
    char usuario[80], senha[80], email[80];

    printf("\n--- TELA DE LOGIN ---\n");
    printf("Usuario: ");
    scanf("%s", usuario);
    limparBuffer();

    printf("Senha: ");
    scanf("%s", senha);
    limparBuffer();

    if (strcmp(usuario, "teste") != 0 || strcmp(senha, "teste1234") != 0) {
        printf("\nUsuario ou senha incorretos.");
        return 0;
    }

    while (1) {
        printf("E-mail: ");
        scanf("%s", email);
        limparBuffer();

        if (strchr(email, '@') == NULL) {
            printf("O e-mail informado deve conter '@', tente novamente.\n");
            continue;
        }

        FILE *arquivoEmails = fopen("emails_usados.txt", "r");
        int emailJaExiste = 0;
        if (arquivoEmails != NULL) {
            char emailSalvo[80];
            while (fscanf(arquivoEmails, "%s", emailSalvo) != EOF) {
                if (strcmp(email, emailSalvo) == 0) {
                    emailJaExiste = 1;
                    break;
                }
            }
            fclose(arquivoEmails);
        }

        if (emailJaExiste) {
            printf("Este e-mail ja foi utilizado, tente novamente.\n");
            continue;
        }

        arquivoEmails = fopen("emails_usados.txt", "a");
        if (arquivoEmails != NULL) {
            fprintf(arquivoEmails, "%s\n", email);
            fclose(arquivoEmails);
        }
        break;
    }
    
    return 1;
}

void exibirMenuPrincipal() {
    printf("\n--- BEM VINDO(A) ACAITERIA BOM SABOR ---\n");
    printf("1. Registrar Pedido\n");
    printf("2. Listar Todos os Pedidos\n");
    printf("3. Editar um Pedido\n");
    printf("4. Excluir um Pedido\n");
    printf("---------------------------\n");
    printf("5. Calcular Faturamento Total\n");
    printf("6. Buscar Pedido por Cliente\n");
    printf("7. Listar Pedidos por Tamanho\n");
    printf("8. Listar Pedidos com Mais de 'N' Adicionais\n");
    printf("9. Listar Pedidos Acima de um Valor\n");
    printf("---------------------------\n");
    printf("0. Sair\n");
}

void registrarPedido() {
    Acai novoPedido;
    printf("\n--- Registrar Novo Pedido ---\n");
    printf("Nome do Cliente: ");
    fgets(novoPedido.nomeCliente, 80, stdin);
    novoPedido.nomeCliente[strcspn(novoPedido.nomeCliente, "\n")] = 0;
    printf("Tamanho do copo (ex: 300ml, 500ml, 700ml): ");
    fgets(novoPedido.tamanho, 80, stdin);
    novoPedido.tamanho[strcspn(novoPedido.tamanho, "\n")] = 0;
    printf("Quantidade de adicionais: ");
    scanf("%d", &novoPedido.numAdicionais);
    limparBuffer();
    novoPedido.preco = calcularPreco(novoPedido.tamanho, novoPedido.numAdicionais);
    printf("Preco do pedido: R$ %.2f\n", novoPedido.preco);
    FILE *arquivo = fopen("pedidos_acai.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de pedidos!\n");
        return;
    }
    fprintf(arquivo, "%s;%s;%d;%.2f\n", novoPedido.nomeCliente, novoPedido.tamanho, novoPedido.numAdicionais, novoPedido.preco);
    fclose(arquivo);
    printf("Pedido registrado com sucesso!\n");
}

void listarPedidos() {
    FILE *arquivo = fopen("pedidos_acai.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum pedido registrado.\n");
        return;
    }
    Acai p;
    int contador = 0;
    printf("\n--- Lista de Pedidos ---\n");
    while (fscanf(arquivo, "%[^;];%[^;];%d;%f\n", p.nomeCliente, p.tamanho, &p.numAdicionais, &p.preco) == 4) {
        imprimirDetalhesPedido(p);
        contador++;
    }
    if (contador > 0) {
        printf("----------------------------------------\n");
    } else {
        printf("Nenhum pedido registrado.\n");
    }
    fclose(arquivo);
}

void editarPedido() {
    char nomeBusca[80];
    printf("\n--- Editar Pedido ---\n");
    printf("Nome do cliente para editar: ");
    fgets(nomeBusca, 80, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    FILE *original = fopen("pedidos_acai.txt", "r");
    FILE *temporario = fopen("temp_pedidos.txt", "w");
    if (original == NULL || temporario == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }
    Acai p;
    int encontrado = 0;
    while (fscanf(original, "%[^;];%[^;];%d;%f\n", p.nomeCliente, p.tamanho, &p.numAdicionais, &p.preco) == 4) {
        if (strcmp(p.nomeCliente, nomeBusca) == 0) {
            encontrado = 1;
            printf("Novo Tamanho: ");
            fgets(p.tamanho, 80, stdin);
            p.tamanho[strcspn(p.tamanho, "\n")] = 0;
            printf("Nova Quantidade de Adicionais: ");
            scanf("%d", &p.numAdicionais);
            limparBuffer();
            p.preco = calcularPreco(p.tamanho, p.numAdicionais);
            fprintf(temporario, "%s;%s;%d;%.2f\n", p.nomeCliente, p.tamanho, p.numAdicionais, p.preco);
            printf("Pedido atualizado com sucesso!\n");
        } else {
            fprintf(temporario, "%s;%s;%d;%.2f\n", p.nomeCliente, p.tamanho, p.numAdicionais, p.preco);
        }
    }
    fclose(original);
    fclose(temporario);
    remove("pedidos_acai.txt");
    rename("temp_pedidos.txt", "pedidos_acai.txt");
    if (!encontrado) {
        printf("\nPedido nao encontrado.\n");
    }
}

void excluirPedido() {
    char nomeBusca[80];
    printf("\n--- Excluir Pedido ---\n");
    printf("Nome do cliente para excluir: ");
    fgets(nomeBusca, 80, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    FILE *original = fopen("pedidos_acai.txt", "r");
    FILE *temporario = fopen("temp_pedidos.txt", "w");
    if (original == NULL || temporario == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }
    Acai p;
    int encontrado = 0;
    while (fscanf(original, "%[^;];%[^;];%d;%f\n", p.nomeCliente, p.tamanho, &p.numAdicionais, &p.preco) == 4) {
        if (strcmp(p.nomeCliente, nomeBusca) == 0) {
            encontrado = 1;
        } else {
            fprintf(temporario, "%s;%s;%d;%.2f\n", p.nomeCliente, p.tamanho, p.numAdicionais, p.preco);
        }
    }
    fclose(original);
    fclose(temporario);
    remove("pedidos_acai.txt");
    rename("temp_pedidos.txt", "pedidos_acai.txt");
    if (encontrado) {
        printf("Pedido excluido com sucesso!\n");
    } else {
        printf("\nPedido nao encontrado.\n");
    }
}

void calcularFaturamentoTotal() {
    FILE *arquivo = fopen("pedidos_acai.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum pedido registrado.\n");
        return;
    }
    Acai p;
    float faturamento = 0.0;
    int totalPedidos = 0;
    while (fscanf(arquivo, "%[^;];%[^;];%d;%f\n", p.nomeCliente, p.tamanho, &p.numAdicionais, &p.preco) == 4) {
        faturamento += p.preco;
        totalPedidos++;
    }
    fclose(arquivo);
    printf("\n--- Faturamento Total ---\n");
    printf("Total de pedidos: %d\n", totalPedidos);
    printf("Faturamento total: R$ %.2f\n", faturamento);
}

void buscarPedidoPorCliente() {
    char nomeBusca[80];
    printf("\n--- Buscar Pedido por Cliente ---\n");
    printf("Digite o nome do cliente para buscar: ");
    fgets(nomeBusca, 80, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    FILE *arquivo = fopen("pedidos_acai.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum pedido registrado.\n");
        return;
    }
    Acai p;
    int encontrados = 0;
    printf("\nResultados da busca:\n");
    while (fscanf(arquivo, "%[^;];%[^;];%d;%f\n", p.nomeCliente, p.tamanho, &p.numAdicionais, &p.preco) == 4) {
        if (stricmp(p.nomeCliente, nomeBusca) == 0) {
            imprimirDetalhesPedido(p);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum pedido encontrado para este cliente.\n");
    }
    fclose(arquivo);
}

void listarPedidosPorTamanho() {
    char tamanhoBusca[80];
    printf("\n--- Listar Pedidos por Tamanho ---\n");
    printf("Digite o tamanho para buscar (ex: 500ml): ");
    fgets(tamanhoBusca, 80, stdin);
    tamanhoBusca[strcspn(tamanhoBusca, "\n")] = 0;

    FILE *arquivo = fopen("pedidos_acai.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum pedido registrado.\n");
        return;
    }
    Acai p;
    int encontrados = 0;
    printf("\nPedidos de tamanho '%s':\n", tamanhoBusca);
    while (fscanf(arquivo, "%[^;];%[^;];%d;%f\n", p.nomeCliente, p.tamanho, &p.numAdicionais, &p.preco) == 4) {
        if (stricmp(p.tamanho, tamanhoBusca) == 0) {
            imprimirDetalhesPedido(p);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum pedido encontrado para este tamanho.\n");
    }
    fclose(arquivo);
}

void listarPedidosComMaisDeNAdicionais() {
    int n;
    printf("\n--- Listar Pedidos por No. de Adicionais ---\n");
    printf("Mostrar pedidos com mais de quantos adicionais? ");
    scanf("%d", &n);
    limparBuffer();

    FILE *arquivo = fopen("pedidos_acai.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum pedido registrado.\n");
        return;
    }
    Acai p;
    int encontrados = 0;
    printf("\nPedidos com mais de %d adicional(is):\n", n);
    while (fscanf(arquivo, "%[^;];%[^;];%d;%f\n", p.nomeCliente, p.tamanho, &p.numAdicionais, &p.preco) == 4) {
        if (p.numAdicionais > n) {
            imprimirDetalhesPedido(p);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum pedido encontrado com mais de %d adicional(is).\n", n);
    }
    fclose(arquivo);
}

void listarPedidosAcimaDeValor() {
    float valorBusca;
    printf("\n--- Listar Pedidos Acima de um Valor ---\n");
    printf("Mostrar pedidos com valor acima de: R$ ");
    scanf("%f", &valorBusca);
    limparBuffer();

    FILE *arquivo = fopen("pedidos_acai.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum pedido registrado.\n");
        return;
    }
    Acai p;
    int encontrados = 0;
    printf("\nPedidos com valor acima de R$ %.2f:\n", valorBusca);
    while (fscanf(arquivo, "%[^;];%[^;];%d;%f\n", p.nomeCliente, p.tamanho, &p.numAdicionais, &p.preco) == 4) {
        if (p.preco > valorBusca) {
            imprimirDetalhesPedido(p);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum pedido encontrado acima deste valor.\n");
    }
    fclose(arquivo);
}