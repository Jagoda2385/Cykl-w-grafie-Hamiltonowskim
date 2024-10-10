#include <stdio.h>
#include <stdlib.h>

int** tworzenie_grafu(const char* filename, int* wierzcholki, int* krawedzie) {
    // Otwórz plik do odczytu
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Nie można otworzyć pliku");
        return NULL;
    }

    // Wczytaj liczbę wierzchołków i krawędzi
    fscanf(file, "%d %d", wierzcholki, krawedzie);

    // Alokacja macierzy sąsiedztwa
    int** macierz_sasiedztwa = (int**)malloc((*wierzcholki) * sizeof(int*));
    for (int i = 0; i < *wierzcholki; i++) {
        macierz_sasiedztwa[i] = (int*)malloc((*wierzcholki) * sizeof(int));
        // Inicjalizacja macierzy zerami
        for (int j = 0; j < *wierzcholki; j++) {
            macierz_sasiedztwa[i][j] = 0;
        }
    }

    // Wczytywanie krawędzi i aktualizacja macierzy sąsiedztwa
    for (int i = 0; i < *krawedzie; i++) {
        int a, b;
        fscanf(file, "%d %d", &a, &b);
        macierz_sasiedztwa[a][b] = 1;
        macierz_sasiedztwa[b][a] = 1; // dla grafu nieskierowanego
    }

    // Zamknięcie pliku
    fclose(file);
    
    return macierz_sasiedztwa;
}

void zwolnij_macierz(int** macierz, int wierzcholki) {
    for (int i = 0; i < wierzcholki; i++) {
        free(macierz[i]);
    }
    free(macierz);
}

int main() {
    int wierzcholki, krawedzie;
    const char* filename = "dane.txt";

    int** macierz_sasiedztwa = tworzenie_grafu(filename, &wierzcholki, &krawedzie);
    if (macierz_sasiedztwa == NULL) {
        return 1; // Błąd w tworzeniu grafu
    }

    // Wypisanie macierzy sąsiedztwa
    for (int i = 0; i < wierzcholki; i++) {
        for (int j = 0; j < wierzcholki; j++) {
            printf("%d ", macierz_sasiedztwa[i][j]);
        }
        printf("\n");
    }

    // Zwolnienie pamięci
    zwolnij_macierz(macierz_sasiedztwa, wierzcholki);

    return 0;
}
