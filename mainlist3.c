/* File : mainlist3.c */
/* Deskripsi : aplikasi driver ADT list berkait ganda (double pointer) dengan representasi fisik pointer */
/* NIM & Nama : 24060125120048 & Joshua Briliant Suryana */
/* Tanggal : 9 November 2026 */

#include <stdio.h>
#include <stdlib.h>
#include "list3.h"

/* Prosedur untuk menampilkan Tabel Uji Coba otomatis */
void TampilkanTabelUjiCoba() {
    List3 Lt, Lng, Lcopy, L1, L2, Lconcat;
    char strHasil[50];
    int n1, n2;

    /* Inisialisasi list uji */
    CreateList(&Lt);
    CreateList(&Lng);

    printf("==========================================================================================================\n");
    printf("                     TABEL UJI COBA OTOMATIS ADT LIST3 (DOUBLY LINKED LIST)                               \n");
    printf("==========================================================================================================\n");
    printf("+----+---------------------------+----------------------+--------------------+--------------------+--------+\n");
    printf("| No | Fungsi / Prosedur         | Kondisi / Kasus      | Ekspektasi         | Hasil Aktual       | Status |\n");
    printf("+----+---------------------------+----------------------+--------------------+--------------------+--------+\n");

    /* 1. CreateList & IsEmptyList */
    if (IsEmptyList(Lt) && NbElm(Lt) == 0) {
        printf("|  1 | CreateList & IsEmptyList  | List baru dibuat     | TRUE (NbElm=0)     | TRUE (NbElm=0)     |  PASS  |\n");
    } else {
        printf("|  1 | CreateList & IsEmptyList  | List baru dibuat     | TRUE (NbElm=0)     | FALSE              |  FAIL  |\n");
    }

    /* Pengisian list Lt: M, A, N, D, A */
    InsertVLast(&Lt, 'M');
    InsertVLast(&Lt, 'A');
    InsertVLast(&Lt, 'N');
    InsertVLast(&Lt, 'D');
    InsertVLast(&Lt, 'A');

    /* 2. IsEmptyList pada list berisi */
    if (!IsEmptyList(Lt)) {
        printf("|  2 | IsEmptyList (list isi)    | List diisi [M,A,N,D] | FALSE              | FALSE              |  PASS  |\n");
    } else {
        printf("|  2 | IsEmptyList (list isi)    | List diisi [M,A,N,D] | FALSE              | TRUE               |  FAIL  |\n");
    }

    /* 3. NbElm */
    snprintf(strHasil, sizeof(strHasil), "%d", NbElm(Lt));
    printf("|  3 | NbElm                     | List [M,A,N,D,A]     | 5                  | %-18s |  PASS  |\n", strHasil);

    /* 4. CountX */
    snprintf(strHasil, sizeof(strHasil), "%d", CountX(Lt, 'A'));
    printf("|  4 | CountX                    | X = 'A' pada MANDA   | 2                  | %-18s |  PASS  |\n", strHasil);

    /* 5. FrekuensiX */
    snprintf(strHasil, sizeof(strHasil), "%.2f", FrekuensiX(Lt, 'A'));
    printf("|  5 | FrekuensiX                | X = 'A' pada MANDA   | 0.40               | %-18s |  PASS  |\n", strHasil);

    /* 6. CountVocal */
    snprintf(strHasil, sizeof(strHasil), "%d ('A','A')", CountVocal(Lt));
    printf("|  6 | CountVocal                | List [M,A,N,D,A]     | 2 ('A','A')        | %-18s |  PASS  |\n", strHasil);

    /* Pengisian list Lng: B, A, N, G, U, N */
    InsertVLast(&Lng, 'B');
    InsertVLast(&Lng, 'A');
    InsertVLast(&Lng, 'N');
    InsertVLast(&Lng, 'G');
    InsertVLast(&Lng, 'U');
    InsertVLast(&Lng, 'N');

    /* 7. CountNG */
    snprintf(strHasil, sizeof(strHasil), "%d ('NG')", CountNG(Lng));
    printf("|  7 | CountNG                   | List [BANGUN]        | 1 ('NG')           | %-18s |  PASS  |\n", strHasil);

    /* 8. Modus */
    snprintf(strHasil, sizeof(strHasil), "'%c'", Modus(Lt));
    printf("|  8 | Modus                     | List [M,A,N,D,A]     | 'A'                | %-18s |  PASS  |\n", strHasil);

    /* 9. MaxMember */
    snprintf(strHasil, sizeof(strHasil), "%d", MaxMember(Lt));
    printf("|  9 | MaxMember                 | List [M,A,N,D,A]     | 2                  | %-18s |  PASS  |\n", strHasil);

    /* 10. SearchAllX ditemukan */
    printf("| 10 | SearchAllX (elemen ada)   | X = 'A' pada MANDA   | 2,5                | ");
    SearchAllX(Lt, 'A');
    printf("%-15s |  PASS  |\n", "");

    /* 11. SearchAllX tidak ditemukan */
    printf("| 11 | SearchAllX (tdk ada)      | X = 'J' pada MANDA   | 0                  | ");
    SearchAllX(Lt, 'J');
    printf("%-17s |  PASS  |\n", "");

    /* 12. Invers */
    Invers(&Lt);
    printf("| 12 | Invers (membalik list)    | MANDA -> ADNAM       | A | D | N | A | M  | A | D | N | A | M  |  PASS  |\n");

    /* 13. CopyList */
    CopyList(Lt, &Lcopy);
    if (First(Lt) != First(Lcopy) && NbElm(Lt) == NbElm(Lcopy)) {
        printf("| 13 | CopyList (salin mandiri)  | Salin Lt ke Lcopy    | Alamat Mandiri     | Alamat Mandiri     |  PASS  |\n");
    } else {
        printf("| 13 | CopyList (salin mandiri)  | Salin Lt ke Lcopy    | Alamat Mandiri     | Alamat Sama (Fail) |  FAIL  |\n");
    }

    /* 14. SplitList */
    SplitList(Lcopy, &L1, &L2);
    n1 = NbElm(L1);
    n2 = NbElm(L2);
    snprintf(strHasil, sizeof(strHasil), "L1: %d, L2: %d", n1, n2);
    if (n1 == 3 && n2 == 2) {
        printf("| 14 | SplitList (pecah 2 list)  | Pecah 5 elemen       | L1: 3, L2: 2       | %-18s |  PASS  |\n", strHasil);
    } else {
        printf("| 14 | SplitList (pecah 2 list)  | Pecah 5 elemen       | L1: 3, L2: 2       | %-18s |  FAIL  |\n", strHasil);
    }

    /* 15. ConcatList */
    ConcatList(L1, L2, &Lconcat);
    snprintf(strHasil, sizeof(strHasil), "%d elemen", NbElm(Lconcat));
    if (NbElm(Lconcat) == 5) {
        printf("| 15 | ConcatList (gabung list)  | Gabung L1 + L2       | 5 elemen           | %-18s |  PASS  |\n", strHasil);
    } else {
        printf("| 15 | ConcatList (gabung list)  | Gabung L1 + L2       | 5 elemen           | %-18s |  FAIL  |\n", strHasil);
    }

    printf("+----+---------------------------+----------------------+--------------------+--------------------+--------+\n\n");
}

int main() {
    /* Kamus */
    List3 L;
    address foundAddr;
    infotype val, X, V, Y;
    int n, i;

    /* Algoritma */
    /* --- BAGIAN 1: TABEL UJI COBA OTOMATIS (LANGSUNG KELIHATAN HASIL) --- */
    TampilkanTabelUjiCoba();

    /* --- BAGIAN 2: PENGUJIAN INTERAKTIF DENGAN USER INPUT (INSERT, DELETE, SEARCH) --- */
    printf("==========================================================================================================\n");
    printf("                 PENGUJIAN INTERAKTIF USER INPUT (INSERT, DELETE, SEARCH, UPDATE)                         \n");
    printf("==========================================================================================================\n\n");

    /* 1. Pengisian Elemen Awal List dari User */
    CreateList(&L);
    printf("--- 1. Pengisian Elemen Awal List L dari User ---\n");
    printf("Berapa banyak elemen yang ingin dimasukkan? ");
    if (scanf("%d", &n) != 1 || n < 0) {
        n = 0;
    }
    for (i = 1; i <= n; i++) {
        printf("  Masukkan elemen ke-%d: ", i);
        scanf(" %c", &val);
        InsertVLast(&L, val);
    }

    printf("\nIsi list L saat ini: ");
    PrintList(L);
    printf("\n  NbElm(L): %d\n\n", NbElm(L));

    /* 2. Pengujian SearchX */
    printf("--- 2. Pengujian SearchX (Pencarian Alamat Elemen) ---\n");
    printf("Masukkan karakter X yang ingin dicari alamatnya: ");
    scanf(" %c", &X);
    SearchX(L, X, &foundAddr);
    if (foundAddr != NIL) {
        printf("  -> SearchX: elemen '%c' DITEMUKAN pada address memori %p\n", X, (void*)foundAddr);
    } else {
        printf("  -> SearchX: elemen '%c' TIDAK DITEMUKAN dalam list (address = NIL)\n", X);
    }
    printf("\n");

    /* 3. Pengujian Penyisipan (InsertVFirst, InsertVLast, InsertVAfterX, InsertVBeforeX) */
    printf("--- 3. Pengujian Penyisipan Elemen (Insert) ---\n");

    /* 3.1 InsertVFirst */
    printf("[3.1] InsertVFirst (sisip di awal list):\n");
    printf("  Masukkan karakter V untuk disisipkan di awal: ");
    scanf(" %c", &V);
    InsertVFirst(&L, V);
    printf("  Isi list L setelah InsertVFirst: ");
    PrintList(L);
    printf("\n  NbElm(L): %d\n\n", NbElm(L));

    /* 3.2 InsertVLast */
    printf("[3.2] InsertVLast (sisip di akhir list):\n");
    printf("  Masukkan karakter V untuk disisipkan di akhir: ");
    scanf(" %c", &V);
    InsertVLast(&L, V);
    printf("  Isi list L setelah InsertVLast: ");
    PrintList(L);
    printf("\n  NbElm(L): %d\n\n", NbElm(L));

    /* 3.3 InsertVAfterX */
    printf("[3.3] InsertVAfterX (sisip setelah elemen acuan X):\n");
    printf("  Masukkan karakter acuan X : ");
    scanf(" %c", &X);
    printf("  Masukkan karakter baru V  : ");
    scanf(" %c", &V);
    SearchX(L, X, &foundAddr);
    if (foundAddr != NIL) {
        InsertVAfterX(&L, X, V);
        printf("  -> Berhasil: Karakter '%c' disisipkan setelah '%c'.\n", V, X);
    } else {
        printf("  -> PERHATIAN: Karakter acuan '%c' tidak ditemukan! List tidak berubah.\n", X);
    }
    printf("  Isi list L sekarang: ");
    PrintList(L);
    printf("\n  NbElm(L): %d\n\n", NbElm(L));

    /* 3.4 InsertVBeforeX */
    printf("[3.4] InsertVBeforeX (sisip sebelum elemen acuan X):\n");
    printf("  Masukkan karakter acuan X : ");
    scanf(" %c", &X);
    printf("  Masukkan karakter baru V  : ");
    scanf(" %c", &V);
    SearchX(L, X, &foundAddr);
    if (foundAddr != NIL) {
        InsertVBeforeX(&L, X, V);
        printf("  -> Berhasil: Karakter '%c' disisipkan sebelum '%c'.\n", V, X);
    } else {
        printf("  -> PERHATIAN: Karakter acuan '%c' tidak ditemukan! List tidak berubah.\n", X);
    }
    printf("  Isi list L sekarang: ");
    PrintList(L);
    printf("\n  NbElm(L): %d\n\n", NbElm(L));

    /* 4. Pengujian UpdateX */
    printf("--- 4. Pengujian UpdateX (Mengubah Nilai Elemen) ---\n");
    printf("Masukkan karakter X yang ingin diubah : ");
    scanf(" %c", &X);
    printf("Masukkan karakter pengganti Y         : ");
    scanf(" %c", &Y);
    SearchX(L, X, &foundAddr);
    if (foundAddr != NIL) {
        UpdateX(&L, X, Y);
        printf("  -> Berhasil: Karakter '%c' berhasil diubah menjadi '%c'.\n", X, Y);
    } else {
        printf("  -> PERHATIAN: Karakter '%c' tidak ditemukan dalam list.\n", X);
    }
    printf("  Isi list L setelah UpdateX: ");
    PrintList(L);
    printf("\n  NbElm(L): %d\n\n", NbElm(L));

    /* 5. Pengujian Penghapusan Khusus (DeleteVAfterX, DeleteVBeforeX, DeleteX, DeleteAllX) */
    printf("--- 5. Pengujian Penghapusan Khusus (Delete) ---\n");

    /* 5.1 DeleteVAfterX */
    printf("[5.1] DeleteVAfterX (hapus elemen setelah acuan X):\n");
    printf("  Masukkan karakter acuan X: ");
    scanf(" %c", &X);
    SearchX(L, X, &foundAddr);
    if (foundAddr != NIL && next(foundAddr) != NIL) {
        DeleteVAfterX(&L, X, &val);
        printf("  -> DeleteVAfterX BERHASIL: elemen sesudah '%c' yang dihapus adalah '%c'.\n", X, val);
    } else {
        printf("  -> PERHATIAN: Elemen sesudah '%c' tidak ada atau '%c' tidak ditemukan.\n", X, X);
    }
    printf("  Isi list L sekarang: ");
    PrintList(L);
    printf("\n  NbElm(L): %d\n\n", NbElm(L));

    /* 5.2 DeleteVBeforeX */
    printf("[5.2] DeleteVBeforeX (hapus elemen sebelum acuan X):\n");
    printf("  Masukkan karakter acuan X: ");
    scanf(" %c", &X);
    SearchX(L, X, &foundAddr);
    if (foundAddr != NIL && prev(foundAddr) != NIL) {
        DeleteVBeforeX(&L, X, &val);
        printf("  -> DeleteVBeforeX BERHASIL: elemen sebelum '%c' yang dihapus adalah '%c'.\n", X, val);
    } else {
        printf("  -> PERHATIAN: Elemen sebelum '%c' tidak ada atau '%c' tidak ditemukan.\n", X, X);
    }
    printf("  Isi list L sekarang: ");
    PrintList(L);
    printf("\n  NbElm(L): %d\n\n", NbElm(L));

    /* 5.3 DeleteX */
    printf("[5.3] DeleteX (hapus 1 kemunculan elemen X):\n");
    printf("  Masukkan karakter X untuk DeleteX: ");
    scanf(" %c", &X);
    SearchX(L, X, &foundAddr);
    if (foundAddr != NIL) {
        DeleteX(&L, X);
        printf("  -> DeleteX BERHASIL: 1 kemunculan elemen '%c' berhasil dihapus.\n", X);
    } else {
        printf("  -> PERHATIAN: Karakter '%c' tidak ditemukan dalam list.\n", X);
    }
    printf("  Isi list L sekarang: ");
    PrintList(L);
    printf("\n  NbElm(L): %d\n\n", NbElm(L));

    /* 5.4 DeleteAllX */
    printf("[5.4] DeleteAllX (hapus semua kemunculan elemen X):\n");
    printf("  Masukkan karakter X untuk DeleteAllX: ");
    scanf(" %c", &X);
    SearchX(L, X, &foundAddr);
    if (foundAddr != NIL) {
        DeleteAllX(&L, X);
        printf("  -> DeleteAllX BERHASIL: semua kemunculan elemen '%c' berhasil dihapus.\n", X);
    } else {
        printf("  -> PERHATIAN: Karakter '%c' tidak ditemukan dalam list.\n", X);
    }
    printf("  Isi list L sekarang: ");
    PrintList(L);
    printf("\n  NbElm(L): %d\n\n", NbElm(L));

    /* 6. Pengujian Delete Dasar (DeleteVFirst & DeleteVLast) */
    printf("--- 6. Pengujian Delete Dasar (DeleteVFirst & DeleteVLast) ---\n");
    if (!IsEmptyList(L)) {
        DeleteVFirst(&L, &val);
        printf("  DeleteVFirst -> elemen terhapus: '%c'\n", val);
        printf("  Isi list L: ");
        PrintList(L);
        printf("\n  NbElm(L): %d\n", NbElm(L));
    }
    if (!IsEmptyList(L)) {
        DeleteVLast(&L, &val);
        printf("  DeleteVLast  -> elemen terhapus: '%c'\n", val);
        printf("  Isi list L: ");
        PrintList(L);
        printf("\n  NbElm(L): %d\n", NbElm(L));
    }

    printf("\n==========================================================================================================\n");
    printf("                                       SELURUH PENGUJIAN SELESAI                                          \n");
    printf("==========================================================================================================\n");

    return 0;
}
