#include <stdio.h>

// Função para aplicar desconto
void aplicarDesconto(float *preco, float desconto) {
    *preco -= (*preco * (desconto / 100));
}

int main() {
    float preco, desconto;
    
    // Solicita o preço do produto
    printf("Digite o preco do produto: ");
    scanf("%f", &preco);
    
    // Solicita o valor do desconto
    printf("Digite o percentual de desconto: ");
    scanf("%f", &desconto);
    
    // Armazena o preço original
    float precoOriginal = preco;
    
    // Aplica o desconto
    aplicarDesconto(&preco, desconto);
    
    // Exibe os resultados
    printf("\nPreco original: R$ %.2f\n", precoOriginal);
    printf("Desconto aplicado: %.2f%%\n", desconto);
    printf("Preco final: R$ %.2f\n", preco);
    
    return 0;
}
