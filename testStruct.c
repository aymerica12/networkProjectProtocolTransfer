typedef struct Personne Personne;
struct Personne{
    int age;
    char nom[100];
};
int main(int argc, char *argv[])
{
    Personne pp;
    printf("age ?");
    scanf("%d",pp.age);
    printf("nom ?");
    scanf("#s",pp.nom);
    printf("nom : %s , age : %d",pp.nom, pp.age);
}
