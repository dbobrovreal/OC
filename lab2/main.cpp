#include <iostream>
#include <fstream>
#include <filesystem>
#include <string.h>
#include <stdio.h>
#include <cstring>
#include <dirent.h> 


using namespace std;
 
void copy() {
  int len;
  char * buffer;
  char file[24], file_copy[24];

  cout << "Введите название файла для копирования: ";
  cin >> file;

  cout << "Введите путь и название файла куда копировать: ";
  cin >> file_copy;
 
  ifstream  infile(file, ios::binary);
  ofstream outfile(file_copy, ios::binary);
 
  infile.seekg (0, ios::end);
  len = infile.tellg();
  infile.seekg (0, ios::beg);
  buffer = new char [len];
 
  infile.read   (buffer,len);
  outfile.write (buffer,len);
 
  delete[] buffer;

}

void moving(){
  int len;
  char * buffer;
  char file[24], file_moving[24];
  
  cout << "Введите файл для перемещения: ";
  cin >> file;

  ifstream  infile(file, ios::binary);
  remove(file);
  cout << "Введите директорию в которую надо переместить файл и название перемещаемого файла : ";
  cin >> file_moving;
  ofstream outfile(file_moving, ios::binary);
 
  infile.seekg (0, ios::end);
  len = infile.tellg();
  infile.seekg (0, ios::beg);
  buffer = new char [len];
 
  infile.read   (buffer,len);
  outfile.write (buffer,len);
 
  delete[] buffer;
}

void delete_file(){
  char file[24];

  cout << "Какой фаил удалить? ";
  cin >> file;

  remove(file);
}

void size_dir()
{
  char file_size[24];

  cout << "Введите файл ";
  cin >> file_size;

  fstream file(file_size);
     int size = 0;
    file.seekg (0, std::ios::end);
    size = file.tellg();
    cout << "Вашь фаил весит : " << size << " баит" << endl;
    file.close();
}

void filename()
{
  DIR *pd;
  struct dirent *dir;
  cout << "Введите имя директории "; 
  
  char name[40];
  cin >> name;

  pd = opendir(name);

  while((dir = readdir(pd))!=NULL)
  {
    if( strcmp( dir->d_name, "." ) == 0 || 
        strcmp( dir->d_name, ".." ) == 0 ) 
    {
      continue;
    }
    
    if(strstr(".",dir->d_name)==NULL)
    {
      cout << dir->d_name << endl;
    }
  }
  closedir(pd);
}
void pr(int tgid){
  char path[40], line[100], *p;
  FILE* statusf;

  snprintf(path, 40, "/proc/%d/status", tgid);

  statusf = fopen(path, "r");
  if (!snprintf)
  {
    return;
  }

  while(fgets(line, 100, statusf)){
    if (strncmp(line, "State:", 6) != 0)
    {
      continue;
    }
    p = line + 7;
    while(isspace(*p)) ++p;

    printf("%6d %s", tgid, p);
    break;
  }
  fclose(statusf);
}

void proc(){
  int c;
  DIR *pd;
  struct dirent *dir;

  pd = opendir("/proc");

  if (pd == NULL){
    cout << "Error";
  }

  while(dir = readdir(pd)){
    if(!isdigit(*dir->d_name)){
      continue;
    }
    c = strtol(dir->d_name, NULL, 10);
    pr(c);
  }
}

int main(int argc, char* argv[]){

  if (argv[1] == NULL){
    cout << "Запустите ./main -help\n";
  }else{
      if (!strcmp(argv[1], "-help"))
      {
        cout << "Авторы:\n\tБобров Данил\n\tЛогутенко Егор\n Все доступные аргументы:\n -c - Копирование файла\n -m - Перемещение файла\n -d - Удаление файла\n -s - Подсчет общего размера указанного файла\n -f - Отображение всех файлов в указанной директории\n -p - Отображение всех процессов из файловой системы procfs\n Кратное описание проекта:\n Работа с файловой системой. Создание проекта «Управление файловой системой»\n Примеры запуска:\n ./main -c\n ./main -m и т.д.\n";
      }
      else if (!strcmp(argv[1], "-c")) {
          copy();
      }
      else if (!strcmp(argv[1], "-m")) {
          moving();
      }  
      else if (!strcmp(argv[1], "-d")) {
          delete_file();
      } 
      else if (!strcmp(argv[1], "-s")) {
          size_dir();
      }
      else if (!strcmp(argv[1], "-f")) {
          filename();
      }
      else if (!strcmp(argv[1], "-p")) {
          proc();
      }
      else  
          cout << "Error\n";

  }

}