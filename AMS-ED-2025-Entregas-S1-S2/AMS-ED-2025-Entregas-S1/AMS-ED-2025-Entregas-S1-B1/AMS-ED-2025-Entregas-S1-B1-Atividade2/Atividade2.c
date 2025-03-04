#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CANDIDATOS 50
#define NOTAS_PE 4
#define NOTAS_AC 5
#define NOTAS_PP 10
#define NOTAS_EB 3

typedef struct {
    char nome[100];
    float pe[NOTAS_PE];
    float ac[NOTAS_AC];
    float pp[NOTAS_PP];
    float eb[NOTAS_EB];
    float nf;
} Candidato;

float lerNota(const char *mensagem) {
    float nota;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%f", &nota) == 1 && nota >= 0 && nota <= 10) {
            getchar(); // Limpar o buffer
            return nota;
        } else {
            printf("Nota inválida. Digite um número entre 0 e 10.\n");
            while (getchar() != '\n'); // Limpar o buffer de entrada
        }
    }
}

void lerNotas(float *notas, int quantidade, const char *mensagem) {
    printf("%s\n", mensagem);
    for (int i = 0; i < quantidade; i++) {
        char msg[100];
        sprintf(msg, "Nota %d: ", i + 1);
        notas[i] = lerNota(msg);
    }
}

float calcularNotaCentral(float *notas, int qtd) {
    float maior = notas[0], menor = notas[0], soma = 0;
    for (int i = 0; i < qtd; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
        soma += notas[i];
    }
    return (soma - maior - menor) / (qtd - 2);
}

void cadastrarCandidato(Candidato *candidatos, int *total) {
    if (*total >= MAX_CANDIDATOS) {
        printf("Limite de candidatos atingido!\n");
        return;
    }

    Candidato *c = &candidatos[*total];
    printf("Nome do candidato: ");
    scanf(" %[^\n]", c->nome);
    getchar();

    lerNotas(c->pe, NOTAS_PE, "Notas da Prova Escrita (PE):");
    lerNotas(c->ac, NOTAS_AC, "Notas da Análise Curricular (AC):");
    lerNotas(c->pp, NOTAS_PP, "Notas da Prova Prática (PP):");
    lerNotas(c->eb, NOTAS_EB, "Notas da Entrevista em Banca (EB):");

    float pe = calcularNotaCentral(c->pe, NOTAS_PE);
    float ac = calcularNotaCentral(c->ac, NOTAS_AC);
    float pp = calcularNotaCentral(c->pp, NOTAS_PP);
    float eb = calcularNotaCentral(c->eb, NOTAS_EB);
    c->nf = (pe * 0.3) + (ac * 0.1) + (pp * 0.4) + (eb * 0.2);
    (*total)++;
}

void exibirRanking(Candidato *candidatos, int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (candidatos[j].nf > candidatos[i].nf) {
                Candidato temp = candidatos[i];
                candidatos[i] = candidatos[j];
                candidatos[j] = temp;
            }
        }
    }

    printf("\nRanking dos 5 melhores candidatos:\n");
    int limite = (total < 5) ? total : 5;
    for (int i = 0; i < limite; i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].nf);
    }
}

int main() {
    Candidato candidatos[MAX_CANDIDATOS];
    int total = 0;
    int opcao;

    do {
        printf("\n1 - Cadastrar Candidato\n2 - Exibir Ranking\n3 - Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarCandidato(candidatos, &total);
                break;
            case 2:
                exibirRanking(candidatos, total);
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);

    return 0;
}