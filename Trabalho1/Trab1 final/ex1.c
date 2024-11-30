#include <stdio.h>

#define VAL_BITS 11
unsigned short encode( int data, int *valid ){
    int inicialData = data;
    int shift = 0;
    int highBits;
    
    if (data == 0){
        *valid = 1;
        return data;
    }
    if (data < 0){
        data = ~data;
    }
    while( ( highBits = data >> (VAL_BITS - 1 )) != 0 && highBits != ~0 ){
        data >>= 1;
        ++shift;
    }
    
    int dataTest = data << shift;
    if (inicialData < 0){
        dataTest = ~dataTest;
        data = ~data;
    }
    if (dataTest != inicialData){
        *valid = 0;
    }else{
        *valid = 1;
    }
    
    return (shift << VAL_BITS) | (data & ~( ~0 << VAL_BITS ));
} 

int decode(unsigned short code)
{
    // Extrair a parte significativa (11 bits)
    int data = code & ((1 << VAL_BITS) - 1);

    // Se o bit de sinal estiver ativo, fazer a extensão de sinal
    if (data & (1 << (VAL_BITS - 1)))
    {
        data |= ~((1 << VAL_BITS) - 1); // Extensão de sinal
    }

    // Extrair o valor do deslocamento (bits 11 a 15)
    int shift = code >> VAL_BITS;

    // Deslocar a parte significativa para a esquerda
    return data << shift;
}

int main()
{
    int data;
    int valid;

    printf("Enter your data: ");
    scanf("%d", &data);

    int encoded = encode(data, &valid);

    if (valid == 0)
    {
        printf("Error: Value cannot be encoded!\n");
    }
    else
    {
        int decoded = decode(encoded);
        printf("Original: %d\nEncoded: 0x%04x\nDecoded: %d\n", data, encoded, decoded);
    }

    return 0;
}
