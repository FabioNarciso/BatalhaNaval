#include <stdio.h>
#include <windows.h>

#define TAM 10 // Tamanho do tabuleiro
#define HAB 5  // Tamanho das matrizes de habilidades (5x5)

// Função para imprimir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM])
{
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    printf("Legenda: 0 = Água | 3 = Navio | 5 = Área de Habilidade\n\n");

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para sobrepor uma habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[HAB][HAB], int origemLinha, int origemColuna)
{
    int centro = HAB / 2;

    for (int i = 0; i < HAB; i++)
    {
        for (int j = 0; j < HAB; j++)
        {
            // Calcula a posição real no tabuleiro
            int linhaTab = origemLinha + (i - centro);
            int colunaTab = origemColuna + (j - centro);

            // Garante que a habilidade não saia do tabuleiro
            if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM)
            {
                // Se a posição faz parte da área de efeito (1), aplica no tabuleiro
                if (habilidade[i][j] == 1)
                {
                    // Marca apenas se não houver navio (não sobrescreve valor 3)
                    if (tabuleiro[linhaTab][colunaTab] != 3)
                        tabuleiro[linhaTab][colunaTab] = 5;
                }
            }
        }
    }
}

int main()
{
    // Configura o terminal para aceitar acentuação (Windows)
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // ===================== ETAPA 1: CRIAR O TABULEIRO =====================
    int tabuleiro[TAM][TAM];

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            tabuleiro[i][j] = 0; // 0 = água
        }
    }

    // ===================== ETAPA 2: CRIAR OS NAVIOS =====================
    int navio[3] = {3, 3, 3};

    // --- Navio 1: Horizontal (linha 2, começando na coluna 4)
    for (int i = 0; i < 3; i++)
        tabuleiro[2][4 + i] = navio[i];

    // --- Navio 2: Vertical (linha 5, começando na coluna 1)
    for (int i = 0; i < 3; i++)
        tabuleiro[5 + i][1] = navio[i];

    // --- Navio 3: Diagonal principal — começa em (0,0)
    for (int i = 0; i < 3; i++)
        if (tabuleiro[i][i] == 0)
            tabuleiro[i][i] = navio[i];

    // --- Navio 4: Diagonal secundária — começa em (0,9)
    for (int i = 0; i < 3; i++)
        if (tabuleiro[i][9 - i] == 0)
            tabuleiro[i][9 - i] = navio[i];

    // ===================== ETAPA 3: CRIAR MATRIZES DE HABILIDADE =====================
    int cone[HAB][HAB];
    int cruz[HAB][HAB];
    int octaedro[HAB][HAB];

    // --- CONE ---
    // O cone aponta para baixo, com o topo na parte superior
    for (int i = 0; i < HAB; i++)
    {
        for (int j = 0; j < HAB; j++)
        {
            if (j >= (HAB / 2 - i) && j <= (HAB / 2 + i) && i <= HAB / 2)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    // --- CRUZ ---
    for (int i = 0; i < HAB; i++)
    {
        for (int j = 0; j < HAB; j++)
        {
            if (i == HAB / 2 || j == HAB / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }

    // --- OCTAEDRO ---
    // Formato de losango (parecido com um diamante)
    for (int i = 0; i < HAB; i++)
    {
        for (int j = 0; j < HAB; j++)
        {
            if (abs(i - HAB / 2) + abs(j - HAB / 2) <= HAB / 2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }

    // ===================== ETAPA 4: APLICAR HABILIDADES AO TABULEIRO =====================
    // Cada habilidade será aplicada em um ponto diferente do tabuleiro
    aplicarHabilidade(tabuleiro, cone, 1, 2);     // Cone centrado em (1,2)
    aplicarHabilidade(tabuleiro, cruz, 5, 5);     // Cruz centrada em (5,5)
    aplicarHabilidade(tabuleiro, octaedro, 7, 8); // Octaedro centrado em (7,8)

    // ===================== ETAPA 5: EXIBIR O RESULTADO FINAL =====================
    exibirTabuleiro(tabuleiro);

    // ===================== ETAPA 6: DEBUG OPCIONAL (mostrar formas das habilidades) =====================
    printf("\n=== MATRIZ CONE ===\n");
    for (int i = 0; i < HAB; i++)
    {
        for (int j = 0; j < HAB; j++)
            printf("%d ", cone[i][j]);
        printf("\n");
    }

    printf("\n=== MATRIZ CRUZ ===\n");
    for (int i = 0; i < HAB; i++)
    {
        for (int j = 0; j < HAB; j++)
            printf("%d ", cruz[i][j]);
        printf("\n");
    }

    printf("\n=== MATRIZ OCTAEDRO ===\n");
    for (int i = 0; i < HAB; i++)
    {
        for (int j = 0; j < HAB; j++)
            printf("%d ", octaedro[i][j]);
        printf("\n");
    }

    return 0;
}
