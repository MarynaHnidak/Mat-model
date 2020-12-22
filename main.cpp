#include <windows.h>
#include <stdio.h>
#define N 101
#include <iostream>
int v[N][N], u[N][N],
    cross0[N][N];	// 1 - ���������� ����, -1 - �����������.
int str0[N],col0[N];	// ���������� ������ � �������.
int strround[N],colround[N];	// ������� �������� (������ �������).
int usestr[N];
int vmax=0;
int sum=0;
int n;
bool ToMax = FALSE;	// ToMax == TRUE  - ������ �� ��������,
				// ToMax == FALSE  - ������ �� �������.
int read(){
int a;
int i,j;

FILE* potok = fopen("C:\\Users\\Lenovo\\Desktop\\input.txt","r");
if(!potok){
   MessageBox(0, "����������� ���� ������� ������!" , ":-(", 16);
   return 0;
   }
fscanf(potok,"%i",&n);
for(i=0; i<n; i++)
   for(j=0; j<n; j++){
      a=fscanf(potok,"%i",&v[i][j]);
      if(a==0 || a==EOF){
         MessageBox(0,"�������� ������ ������!",":-(",16);
         return 0;
         }
      }
fclose(potok);
return 1;
}

	// ������� ���������� ������ �� �����.





	// ���������� �������
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
for(i=0; i<n; i++){	// ���������� �� �������.
   umin=u[i][0];
   for(j=1; j<n; j++)	// ������� � ������.
      umin = umin < u[i][j] ? umin : u[i][j];
   for(j=0; j<n; j++)
      u[i][j]-=umin;
   }
for(j=0; j<n; j++){	// ���������� �� ��������.
   umin=u[0][j];
   for(i=1; i<n; i++)	// ������� � �������.
      umin = umin < u[i][j] ? umin : u[i][j];
   for(i=0; i<n; i++)
      u[i][j]-=umin;
   }
}

void mark0(){	// �������� � ����������� ����.
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
   // ���� ���� ��������� � � ���� ������ ��� �� ����
   if(cross0[i1][j]==-1 && !usestr[i1]){
      // ���� ������ �� ��������
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

	// ���������� �������������.
int upcouple(){
int i,j;
for(i=0; i<n; i++)
   usestr[i]=0;		// � ����� ������ ��������.
for(j=0; j<n; j++)
   if(!col0[j])
      for(i=0; i<n; i++)
         if(cross0[i][j]==-1){	// ����������� ���� � ������������ �������.
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

	// ���������� ������������� �������������.
void maxcouple(){
while(upcouple());
}

	// �������� �� ���������� ������.
int fin(){
int i;
for(i=0; i<n; i++)
   if(!str0[i])
      return 0;
return 1;
}

	// ���������� ����������� �����.
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

	// ������������ �����.
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

	// ������ ����������.
void print(){
    int i,j;
    for(int i=0; i<n; i++){
        printf("� %3i-�� ������ ", i+1);
        for(int j=0; j<n; j++)
            if(cross0[i][j]==1){
               printf("� %3i �������.\n",j+1);
               sum += v[i][j];
               break;
            }
        }printf("\n(���� �����������: %d)\n",sum);}
void method(BOOL ToMax){	// ToMax == TRUE  - ������ �� ��������,
				// ToMax == FALSE  - ������ �� �������.
if(!read())
    return;

    }
void answer(BOOL ToMax){
FILE* potok = fopen("C:\\Users\\Lenovo\\Desktop\\output.txt","w");
int i,j;
int sum=0;
fprintf(potok,"           ����� �����������\n");
for(i=0; i<n; i++){
   fprintf(potok,"� %3i-�� ����� ",i+1);
   for(j=0; j<n; j++)
      if(cross0[i][j]==1){
         fprintf(potok,"� %3i �������.\n",j+1);
         sum+=v[i][j];
         break;
         }
   }
if(ToMax)
   fprintf(potok,"\n(������������ ��������� �������������: %i)\n",sum);
else
   fprintf(potok,"\n(���������� ���� �����������: %i)\n",sum);
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
    MessageBox(0,"��� ����������.","���������",64);
   }
