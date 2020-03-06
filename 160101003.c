#include "160101003.h"

int main(int argc, char *argv[])
{

    struct data* arr = malloc(30 * sizeof(*arr));
    FILE* file = fopen("person.txt", "r+");
    if (!file)
        return -1;

    char buffer[BUFFER_SIZE];
    int flag = 0;
    while (fgets(buffer, BUFFER_SIZE, file))
    {
        arr[flag] = saveToStruct(buffer);
        flag++;
    }

    //Herhangi bir parametre girmeden program çalıştırıldığında.
    if (argc == 1) {
      printf("Admin Komutları:\n");
      printf("./yalphone –a update <userid> <name or phone or department> <newInfo>\n");
      printf("./yalphone –a add <userName> <userPhone> <userDepartment>\n");
      printf("./yalphone –a delete <userid>\n\n");

      printf("Kullanıcı Komutları:\n");
      printf("./yalphone –u filter <letter>\n");
      printf("./yalphone –u filter <phone>\n");
      printf("./yalphone –u\n");

      free(arr);
    }

    //-a update
    else if (argc == 6 && strcmp(argv[1], "-a") == 0 && strcmp(argv[2], "update") == 0) {
      if (atoi(argv[3]) < 0 && atoi(argv[3]) > 31) {
        fprintf(stderr, "Geçersiz bir id girdiniz.\n");
      }

      int updateID = atoi(argv[3]) - 1;
      if (strcmp(argv[4], "name") == 0) {
        printf("Eski Ad Soyad:%s\n", arr[updateID].name);
        strcpy(arr[updateID].name, argv[5]);
        printf("Yeni Ad Soyad: %s\n", arr[updateID].name);
      }

      else if (strcmp(argv[4], "phone") == 0) {
        printf("Eski Numara:%ld\n", arr[updateID].number);
        arr[updateID].number = atol(argv[5]);
        printf("Yeni Numara: %ld\n", arr[updateID].number);
      }

      else if (strcmp(argv[4], "department") == 0) {
        printf("Eski Department:%s\n", arr[updateID].department);
        strcpy(arr[updateID].department, argv[5]);
        printf("Yeni Department: %s\n", arr[updateID].department);
      }

      else {
        fprintf(stderr, "Hatalı bir type girdiniz.\n");
      }

      free(arr);
    }

    //-a add
    //Dosyaya ekleme yapılamadığından dolayı flag sayısı arttırılmamıştır. Aksi takdirde flag++ yapıldıktan sonra diğer tüm kod blokları düzgün çalışır.
    else if (argc == 6 && strcmp(argv[1], "-a") == 0 && strcmp(argv[2], "add") == 0) {
      struct data* arrNew = realloc(arr, (flag+1) * sizeof(*arr));

      arrNew[flag].id = flag + 1;
      strcpy(arrNew[flag].name, argv[3]);
      arrNew[flag].number = atol(argv[4]);
      strcpy(arrNew[flag].department, argv[5]);

      printf("ID: %d\n", arrNew[flag].id);
      printf("Ad: %s\n", arrNew[flag].name);
      printf("Numara: %ld\n", arrNew[flag].number);
      printf("Departman: %s \nKişi listeye eklenmiştir.\n", arrNew[flag].department);

      free(arrNew);
    }

    //-a delete -- Girilen id'ye ait kişinin verilerini sıfırlıyor. Daha sonra deleted.txt adlı dosyaya silinen id'yi yazıyor.
    else if (argc == 4 && strcmp(argv[1], "-a") == 0 && strcmp(argv[2], "delete") == 0) {
      int deleteID = atoi(argv[3]) - 1;
      arr[deleteID].id = 0; // text dosyasının içinde " " ile 0 arasında bir fark yok. " " olunca da 0 olarak alıyor.
      strcpy(arr[deleteID].name, " ");
      arr[deleteID].number = 0;
      strcpy(arr[deleteID].department, " ");

      FILE* fDelete = fopen("deleted.txt", "a");
      fprintf(fDelete, "%d\n", atoi(argv[3]));

      fflush(fDelete);
      fclose(fDelete);

      free(arr);
    }

    //-u filter -- numaranın son 4 hanesine veya ismin ilk harfine göre istenilen kişileri listeliyor. Baş harf büyük girilmelidir.
    else if (argc == 4 && strcmp(argv[1], "-u") == 0 && strcmp(argv[2], "filter") == 0) {
      //Baş harf girildiğinde bu kısım çalışıyor.
      if (strlen(argv[3]) == 1) {
        for (int i = 0; i < flag; i++) {
          char firstLetterName[20];
          char inputLetterName[20];
          strcpy(firstLetterName, arr[i].name);
          strcpy(inputLetterName, argv[3]);
          char firstLetter = firstLetterName[1];
          char inputLetter = inputLetterName[0];

          if (firstLetter == inputLetter) {
            printf("ID: %d, Ad Soyad: %s, Numara: %ld, Departman: %s\n", arr[i].id, arr[i].name, arr[i].number, arr[i].department);
          }
        }
      }

      //Numaraya göre sorgu yapıldığında bu kısım çalışıyor.
      else if (strlen(argv[3]) == 4) {
        int lastFourDigit;
        int inputFourDigit = atol(argv[3]);

        for (int i = 0; i < flag; i++) {
          lastFourDigit = arr[i].number % 10000;

          if (lastFourDigit == inputFourDigit) {
            printf("ID: %d, Ad Soyad: %s, Numara: %ld, Departman: %s\n", arr[i].id, arr[i].name, arr[i].number, arr[i].department);
          }
        }
      }

      else {
        fprintf(stderr, "Hatalı parametre girildi.\n");
      }

      free(arr);
    }

    //-u komutu
    else if (argc == 2 && strcmp(argv[1], "-u") == 0) {
      print(arr, 30);
      FILE* fallUsers = fopen("allusers.txt", "a");
      for (int i = 0; i < flag; i++)
      {
          fprintf(fallUsers, "ID: %d, Ad Soyad: %s, Numara: %ld, Departman: %s\n", arr[i].id, arr[i].name, arr[i].number, arr[i].department);
      }
      fflush(fallUsers);
      fclose(fallUsers);

      free(arr);
    }

    else {
      fprintf(stderr, "Hatalı argüman girişi olmuştur.\n");
      free(arr);
    }

    fclose(file);
}
