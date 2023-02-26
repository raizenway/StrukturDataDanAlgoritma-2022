/*  NAMA ANGGOTA    : BANTENG HARISANTOSO   (221524036)
                      MUHAMMAD DAFFA        (221524049)
    KELAS           : 1B-TI4
    PROGRAM         : PROGRAM UNTUK MEMBUAT ARRAY OF LINKED LIST KOTA DAN MAHASISWA
    TANGGAL         : 13 JANUARI 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//STRUKTUR DATA UNTUK NODE
struct Node{
    char* nama;
    char* kota;
    struct Node* next;
    };

//STRUKTUR DATA UNTUK LIST ARRAY
struct ArrayList{
    int jumlah;
    struct Node** array;
};

/*=========================== MODULAR ================================ */
struct ArrayList* buatArrayList(int jumlah)
/*  DESKRIPSI   : Prosedur untuk membuat array list
    I.S         : Tidak ada array list
    F.S         : Sudah teralokasi array list sebanyak variabel jumlah dengan nilai kosong

*/
{
    struct ArrayList* list = (struct ArrayList*) malloc(sizeof(struct ArrayList));
    list->jumlah = jumlah;
    list->array = (struct Node**) malloc(jumlah * sizeof(struct Node*));
    for(int i = 0; i < jumlah; i++){
        list->array[i]=NULL;
    }

    return list;
}

struct Node* buatNode(char* kota, char* nama)
/*  DESKRIPSI   : Prosedur untuk membuat node dengan data kota dan nama
    I.S         : Node masih kosong
    F.S         : Sudah dibentuk beberapa node dengan data kota dan nama
*/
{
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));

    node->kota = kota;
    node->nama = nama;
    node->next = NULL;

    return node;
}

void tambahElemen(struct ArrayList* list, int index, char* kota, char* nama)
/*  DESKRIPSI   : Menambahkan dan menghubungkan antar node
    I.S         : Elemmen belum dibuat
    F.S         : Elemen sudah terbentuk menggunakan prosedur buatNode dan sudah dihubungkan dengan node lain
*/
{
    struct Node* node = buatNode(kota, nama);
    node->next = list->array[index];
    list->array[index] = node;
}

void hapusElemenNama(struct ArrayList* list, char* nama)
/*  DESKRIPSI   : Menghapus salah satu elemen di indeks yang sama
    I.S         : Elemen satu nama masih ada dan terhubung
    F.S         : Elemen sudah terhapus dan elemen sebelumnya sudah terhubung dengan elemen selanjutnya
*/
{
    bool ada = false;
    for(int i = 0; i < list->jumlah ; i++){
        struct Node* first = list->array[i];
        while(first != NULL){
            if(first->nama == nama) {
                if(first == list->array[i]) {
                    // hapus node awal
                    list->array[i] = first->next;
                    first->next = NULL;
                    free(first);
                    ada = true;
                    break;
                }
                else {
                    // hapus node tengah atau akhir
                    struct Node* temp = list->array[i];
                    while(temp->next != first) {
                        temp = temp->next;
                    }
                    temp->next = first->next;
                    first->next = NULL;
                    free(first);
                    ada = true;
                    break;
                }
            }
            first = first->next;
        }
    }

    if(ada == false){
        printf("Tidak ada nama %s yang terdata.\n", nama);
    }
}

void hapusElemenKota(struct ArrayList* list, char* kota)
/*  DESKRIPSI   : Menghapus salah satu elemen di indeks yang sama
    I.S         : Elemen kota masih ada dan terhubung
    F.S         : Elemen kota beserta sambungan-sambungannya (Mahasiswa) terhapus
*/
{
    bool ada = false;
    for(int i = 0; i < list->jumlah; i++){
        struct Node* first = list->array[i];
        struct Node* prev = NULL;
        while(first != NULL){
            if(first->kota == kota) {
                if(first == list->array[i]) {
                    // hapus node awal
                    list->array[i] = first->next;
                    first->next = NULL;
                    free(first);
                    first = list->array[i];
                }
                else {
                    // hapus node tengah atau akhir
                    prev->next = first->next;
                    first->next = NULL;
                    free(first);
                    first = prev->next;
                }
                ada = true;
            }
            else {
                prev = first;
                first = first->next;
            }
        }
    }

    if (ada == false){
        printf("Tidak ada kota %s yang terdata.\n", kota);
    }

}

/*================================ PROGRAM UTAMA ================================*/
int main(){
    //Buatlah array list sejumlah 5
    struct ArrayList* list = buatArrayList(5);

    //Tambahkan elemen dengan parameter(list, indeks, kota, nama)
    tambahElemen(list, 0, "Bandung", "Banteng Harisantoso");
    tambahElemen(list, 0, "Bandung", "Muhammad Daffa");
    tambahElemen(list, 0, "Bandung", "Asep Sudrajat");
    tambahElemen(list, 1, "Jakarta", "Liem Tjaya");
    tambahElemen(list, 1, "Jakarta", "Ferdi Ahmad");
    tambahElemen(list, 2, "Tangerang", "Thoriq M Fadhli");
    tambahElemen(list, 2, "Tangerang", "Muhammad Naruto");
    tambahElemen(list, 3, "Palembang", "Faris Abulkhoir");
    tambahElemen(list, 3, "Palembang", "Raiden Shogun");
    tambahElemen(list, 4, "Cimahi", "Alisha Nara");
    tambahElemen(list, 4, "Cimahi", "Muhammad Fathur R");
    hapusElemenNama(list, "Muhammad Naruto");
    hapusElemenKota(list, "Cimahi");

    //Menampilkan ke layar
    for(int i = 0; i < list->jumlah; i++){
        if(list->array[i] != NULL){
            struct Node* first = list->array[i];
            printf("%s: ", first->kota);
            while(first != NULL){
                printf("%s", first->nama);
                if(first->next != NULL){
                    printf(", ");
                }
                else{
                    printf(".");
                }
                first = first->next;
            }
            printf("\n");
        }
        
    }
    
}