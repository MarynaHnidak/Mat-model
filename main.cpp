#include <windows.h>
#include <stdio.h>
#define N 101
#include <iostream>
int v[N][N], u[N][N],
    cross0[N][N];	// 1 - отмеченный ноль, -1 - зачеркнутый.
int str0[N],col0[N];	// Помеченные строки и столбцы.
int strround[N],colround[N];	// Пометка кружками (вторая пометка).
int usestr[N];
int vmax=0;
int sum=0;
int n;
bool ToMax = FALSE;	// ToMax == TRUE  - задача на максимум,
				// ToMax == FALSE  - задача на минимум.
int read(){
int a;
int i,j;

FILE* potok = fopen("C:\\Users\\Lenovo\\Desktop\\input.txt","r");
if(!potok){
   MessageBox(0, "Отсутствует файл входных данных!" , ":-(", 16);
   return 0;
   }
fscanf(potok,"%i",&n);
for(i=0; i<n; i++)
   for(j=0; j<n; j++){
      a=fscanf(potok,"%i",&v[i][j]);
      if(a==0 || a==EOF){
         MessageBox(0,"Неверный формат данных!",":-(",16);
         return 0;
         }
      }
fclose(potok);
return 1;
}

	// Функция считывания данных из файла.





	// Приведение матрицы
void privod(BOOL ToMax){
int i,j,umin;
for(i=0; i<n; i++)
   for(j=0; j<n; j++)
      vmax = vmax > v[i][j] ? vmax : v[i][j];
if(ToMax){
   for(i=0; i<n; i++)
      for(j=0; j<n; j++)
         u[i][j] = vmax-v[i][j];
   }
else{
   for(i=0; i<n; i++)
      for(j=0; j<n; j++)
         u[i][j] = v[i][j];
   }
for(i=0; i<n; i++){	// Приведение по строкам.
   umin=u[i][0];
   for(j=1; j<n; j++)	// Минимум в строке.
      umin = umin < u[i][j] ? umin : u[i][j];
   for(j=0; j<n; j++)
      u[i][j]-=umin;
   }
for(j=0; j<n; j++){	// Приведение по столбцам.
   umin=u[0][j];
   for(i=1; i<n; i++)	// Минимум в столбце.
      umin = umin < u[i][j] ? umin : u[i][j];
   for(i=0; i<n; i++)
      u[i][j]-=umin;
   }
}

void mark0(){	// Отмечаем и зачеркиваем нули.
int i,j;
for(i=0; i<n; i++)
   for(j=0; j<n; j++)
      cross0[i][j]=0;
for(i=0; i<n; i++)
   str0[i]=col0[i]=0;
for(i=0; i<n; i++)
   for(j=0; j<n; j++)
      if(u[i][j]==0)
         if(str0[i]==0 && col0[j]==0){
            cross0[i][j]=1;
            str0[i]=col0[j]=1;
            }
         else
            cross0[i][j]=-1;
}

int findcouple(int i){
int i1,j=0;
while(cross0[i][j]!=1) j++;
for(i1=0; i1<n; i1++)
   // Если ноль зачеркнут и в этой строке еще не были
   if(cross0[i1][j]==-1 && !usestr[i1]){
      // Если строка не помечена
      if(!str0[i1]){
         str0[i1]=1;
         cross0[i1][j]=1;
         cross0[i][j]=-1;
         return 1;
         }
      else{
         usestr[i1]=1;
         if(findcouple(i1)){
            cross0[i1][j]=1;
            cross0[i][j]=-1;
            return 1;
            }
         }
      }
return 0;
}

	// Нахождение паросочетания.
int upcouple(){
int i,j;
for(i=0; i<n; i++)
   usestr[i]=0;		// В какой строке побывали.
for(j=0; j<n; j++)
   if(!col0[j])
      for(i=0; i<n; i++)
         if(cross0[i][j]==-1){	// Зачеркнутый ноль в непомеченном столбце.
            usestr[i]=1;
            if(findcouple(i)){
               col0[j]=1;
               cross0[i][j]=1;
               return 1;
               }
            else
               usestr[i]=0;
            }
return 0;
}

	// Нахождение максимального паросочетания.
void maxcouple(){
while(upcouple());
}

	// Проверка на решенность задачи.
int fin(){
int i;
for(i=0; i<n; i++)
   if(!str0[i])
      return 0;
return 1;
}

	// Нахождение минимальной опоры.
void minsupport(){
int i,j,b;
for(i=0; i<n; i++)
   strround[i]=colround[i]=0;
for(i=0; i<n; i++)
   strround[i]=1-str0[i];
b=1;
while(b){
   b=0;
   for(i=0; i<n; i++)
      if(strround[i])
         for(j=0; j<n; j++)
            if(cross0[i][j]==-1)
               colround[j]=1;
   for(j=0; j<n; j++)
      if(colround[j])
         for(i=0; i<n; i++)
            if(cross0[i][j]==1 && !strround[i]){
               b=1;
               strround[i]=1;
               }
   }
}

	// Перестановка нулей.
void rotate0(){
int i,j,min=vmax;
for(i=0; i<n; i++)
   if(strround[i])
      for(j=0; j<n; j++)
         if(!colround[j])
            if(min>u[i][j])
               min=u[i][j];
for(i=0; i<n; i++)
   if(!strround[i])
      for(j=0; j<n; j++)
         u[i][j]+=min;
for(j=0; j<n; j++)
   if(!colround[j])
      for(i=0; i<n; i++)
         u[i][j]-=min;
}

	// Выдача результата.
void print(){
    int i,j;
    for(int i=0; i<n; i++){
        printf("З %3i-го складу ", i+1);
        for(int j=0; j<n; j++)
            if(cross0[i][j]==1){
               printf("в %3i магазин.\n",j+1);
               sum += v[i][j];
               break;
            }
        }printf("\n(Сума перевезення: %d)\n",sum);}
void method(BOOL ToMax){	// ToMax == TRUE  - задача на максимум,
				// ToMax == FALSE  - задача на минимум.
if(!read())
    return;

    }
void answer(BOOL ToMax){
FILE* potok = fopen("C:\\Users\\Lenovo\\Desktop\\output.txt","w");
int i,j;
int sum=0;
fprintf(potok,"           Схема перевезення\n");
for(i=0; i<n; i++){
   fprintf(potok,"З %3i-го скада ",i+1);
   for(j=0; j<n; j++)
      if(cross0[i][j]==1){
         fprintf(potok,"в %3i магазин.\n",j+1);
         sum+=v[i][j];
         break;
         }
   }
if(ToMax)
   fprintf(potok,"\n(Максимальная суммарная эффективность: %i)\n",sum);
else
   fprintf(potok,"\n(Минимальна сума перевезення: %i)\n",sum);
fclose(potok);
}
int main()
{
    method(ToMax);
  privod(ToMax);
 setlocale(LC_ALL, "Russian");
    for (int i=0; i<n; i++){
        for (int j = 0; j<n; j++)
            printf("%d\t",v[i][j]);
            printf("\n");  }
while(1){
   mark0();
   maxcouple();
   if(fin())
      break;
   minsupport();
   rotate0();
   }
    print();
    answer(ToMax);
    MessageBox(0,"Все просчитано.","Результат",64);
   }
