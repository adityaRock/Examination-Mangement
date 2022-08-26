#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

typedef struct date
{
    int dd;
    int mm;
    int yy;
}D;

typedef struct student
{
   char name[100];
   D Dob;
   float isa_marks;
   float esa_marks;
   float total_marks;
   char SRN[15];

}S;

typedef struct teacher
{
    char name[100];
    char pass[15];
    char t_id[15];
}T;

typedef struct question
{
    char ques[200];
    char opt_1[100];
    char opt_2[100];
    char opt_3[100];
    char opt_4[100];
    int correct_opt;
    int selected_opt;
    int marks;
}Q;

Q get_question();
void set_paper();
void write_to_qp(Q q);
int read_questions();
void display_qp(Q q,int);

void display(S s,int);
void init(S *s,char srn[]);
void write_to_file(S s);
S check_srn();
void read_from_file();
S edit_student(S);
void enter_marks();
S take_test(S s);
void enter_final_marks(S s);


void main()
{
    int choice ;

    do
    {


        system("cls");
        printf("\n\n 1. Sign in as student.\n 2. Sign in as teacher.\n 0. Exit.\n\n\t Choice : ");
        scanf("%d",&choice);

        //If the user is a Student.
        if(choice == 1)
            {
                S stu;
                char srn[15];

                system("cls");
                // Function to get SRN of the student and save it against his struct.
                // if SRN not already in s1 -> SL_s = total_s+1
                //Else if already present SL_s = that student no.
                //CURRENT_S;

                stu = check_srn();

                int choice_s;
                do
                {
                    system("cls");
                    printf("\n 1. View Personal details.");
                    printf("\n 2. edit Personal details.");
                    printf("\n 3. Take Computer Exam.");  // not available if teacher hasn't entered isa marks;
                    printf("\n 4. View results."); //not available if exam not taken.
                    printf("\n 0. Exit.");
                    printf("\n\n\t Enter your choice : ");
                    scanf("%d",&choice_s);

                    if(choice_s == 1)
                       {
                         display(stu,0);
                         getch();
                       }

                    else if(choice_s == 2)
                        stu = edit_student(stu);


                    else if(choice_s == 3)
                    {
                        if(stu.isa_marks == -1)
                        {
                            printf("\n ISA_marks not updated, Kindly contact your subject teacher.");
                            getch();
                        }

                        else if(stu.esa_marks != -1)
                        {
                            printf("\n You have already taken the test and your marks have been finalised.\n ALL THE BEST!");
                            getch();
                        }


                        else
                        {
                            stu = take_test(stu);
                            stu.total_marks = stu.esa_marks + stu.isa_marks;
                            //printf("\n Total marks : %f",stu.total_marks);
                            enter_final_marks(stu);
                            getch();
                        }


                    }

                    else if(choice_s == 4)
                    {
                        if(stu.esa_marks == -1)
                        {
                            printf("\n Please attempt the exam first.");
                        }

                        else
                        {
                            printf("\n\n\t ISA MARKS : %.1f",stu.isa_marks);
                            printf("\n\t ESA MARKS : %.1f",stu.esa_marks);
                            printf("\n\n TOTAL MARKS SECURED: %.1f",stu.total_marks);
                            printf("\n\n CONGRATULATIONS!");
                        }

                        getch();
                    }


                }while(choice_s != 0);
            }

        // IF the user is a teacher.
        else if(choice == 2)
            {
                system("cls");
                int ch;
                do
                {
                    system("cls");
                    printf("\n 1. Sign in.\n 0. Exit\n\n Enter choice: ");
                    scanf("%d",&ch);

                    system("cls");

                    if(ch == 1)
                    {
                        char password[20],c=' ';
                    int i=0;
                    printf("\n Enter the password [max length 10] : ");
                    while (i<=9)
                    {
                        password[i]=getch();
                        c=password[i];
                        if(c==13) break;
                        else if(c==8)       /*ASCII value of BACKSPACE*/
                        {
                            putch('b');
                            putch(NULL);
                            putch('b');
                            i--;
                            continue;
                        }
                        else printf("*");
                            i++;
                    }
                    password[i]='\0';i=0;

                        if(strcmp(password,"password") == 0)            //if the password matches
                        {

                            int ch1;
                            do
                            {
                                system("cls");
                                printf("\n 1. Assign marks to student. ");
                                printf("\n 2. Set question paper.");
                                printf("\n 3. View results.");
                                printf("\n 0. Exit.");
                                printf("\n\n Enter your choice: ");
                                scanf("%d",&ch1);

                                if(ch1 == 1)
                                {
                                    enter_marks();
                                }

                                if(ch1 == 2)
                                {
                                    set_paper();
                                }
                                if(ch1 == 3)
                                {
                                        S s1[100];
                                        S *s2[100];
                                        S input;
                                        int i=0;
                                        FILE *infile;
                                        infile = fopen("student.dat","r+b");
                                        while((fread(&input, sizeof(S), 1, infile)))
                                        {
                                            if (input.esa_marks != -1)
                                            {
                                                s1[i] = input;
                                                i++;
                                            }

                                        }

                                        fclose(infile);
                                        init_ptr(s1,s2,i);
                                        selection_sort(s2,i);
                                        disp(s2,i);

                                        getch();
                                }
                            }while(ch1 != 0);
                        }

                        else
                        {
                            printf("\n\t Invalid password.");
                            getch();
                        }
                    }

                }while(ch!=0);
            }

            else if(choice == 100)
            {
                read_from_file();
                getch();
            }

            else if(choice == 0)
            {
                break;
            }

            else
            {
                printf("\n\n Invalid choice");
                getch();
            }

    }while(choice!=0);

}

//===================================================================================================================================================

void init(S *s,char srn[])      //to get the input details of the student
{
    s->isa_marks = -1.0;
    s->esa_marks = -1.0;
    s->total_marks = -1.0;
    printf("\n Enter your details:\n Name: ");
    fflush(stdin);
    gets(s->name);
    printf("\n DOB(dd/mm/yyyy): ");
    scanf("%d/%d/%d",&(s->Dob.dd),&(s->Dob.mm),&(s->Dob.yy));
    strcpy(s->SRN,srn);
}

void display(S s,int n)
{
    printf("\n\n Name: %s\n DOB: %d/%d/%d \n SRN: %s \nISA: %.1f ",s.name,s.Dob.dd,s.Dob.mm,s.Dob.yy,s.SRN,s.isa_marks);
    if(n==1)
    {
        printf("\nESA: %.1f\nTotal: %.1f",s.esa_marks,s.total_marks);
    }


    if(s.isa_marks == -1)
        printf("\n\n NOTE: ISA MARKS -1 implies the teacher hasn't updated your marks yet.\n Kindly inform teacher to Enter marks ASAP.");
}

S check_srn()
{
    FILE *infile;
    S input;
    int flag = 0;
    char srn[15];


    system("cls");

    printf("\n\n\t\t SRN : ");
    scanf("%s",&srn);

    // Open student.txt for reading
    infile = fopen ("student.dat", "r+");
    if (infile == NULL)
    {
        FILE *temp;
        temp = fopen("student.dat","w");
        fclose(temp);
    }

    while(fread(&input, sizeof(S), 1, infile))
    {
        if(strcmpi(input.SRN,srn)==0)
        {
            fclose (infile);
            return input;
        }
    }

    //this line is executed only if the current students' srn is not already in the file.

    init(&input,srn);
    fclose(infile);
    write_to_file(input);
    return input;

}

void write_to_file(S s)
{
    FILE *outfile;

    // open file for writing
    outfile = fopen ("student.dat", "a");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    fwrite (&s, sizeof(S), 1, outfile);

    if(fwrite != 0)
        printf("contents to student database written successfully !\n");
    else
        printf("error writing file !\n");

    // close file
    fclose (outfile);
}


S edit_student(S s)
{
    FILE *infile;
    infile = fopen("student.dat","r+b");
    S temp,input;
    char ch;


    while(fread(&input,sizeof(S),1,infile))
    {
        if(strcmpi(s.SRN,input.SRN)==0)
        {
            temp = input;
            printf("\n You are about to modify your details.\n Current details:\n");
            display(temp,0);

            printf("\n Change name?(y/n) : ");
            fflush(stdin);
            scanf("%c",&ch);

            if(ch == 'y')
            {
                printf("\n New name: ");
                fflush(stdin);
                gets(temp.name);
            }

            printf("\n Change DOB?(y/n) : ");
            fflush(stdin);
            scanf("%c",&ch);

            if(ch == 'y')
            {
                printf("\n New DOB(dd/mm/yyyy) : ");
                fflush(stdin);
                scanf("%d/%d/%d",&temp.Dob.dd,&temp.Dob.mm,&temp.Dob.yy);
            }

            fseek(infile,-sizeof(S),SEEK_CUR);
            fwrite(&temp,sizeof(S),1,infile);

            if(fwrite != 0)
                printf("\n Modified succesfuly");
            else
                printf("\n Error modifying file");

                getch();

            fclose(infile);
            return temp;
        }

    }

    printf("\n SRN not in records.");
    getch();
    fclose(infile);
    return s;

}



void read_from_file()           //Read entire data from student.dat
{
    FILE *infile;
    S input;

    // Open person.dat for reading
    infile = fopen ("student.dat", "r+b");
    rewind(infile);
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    while(fread(&input, sizeof(S), 1, infile))
    {
        display(input,1);
    }

    fclose (infile);
}


void enter_marks()          //Function for teacher to enter marks
{
    FILE *infile;
    FILE *outfile;
    S input,temp;
    int flag = 0;
    // Open person.dat for reading
    infile = fopen("student.dat","r+b");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    char choice;

    while(fread(&input, sizeof(S), 1, infile))
    {
        //printf("\n pointing : %d",ftell(infile));
        if(input.isa_marks == -1.0)
        {
            flag = 1;
            int pos = ftell(infile);
            temp = input;
            printf("\n\n SRN : %s",input.SRN);
            printf("\n Enter marks?(y/n) : ");
            fflush(stdin);
            scanf("%c",&choice);
            if(choice=='y'&& !feof(infile))
            {
                printf("\nMarks Secured : ");
                fflush(stdin);
                scanf("%f",&temp.isa_marks);

                fseek(infile,-sizeof(S),SEEK_CUR);
                //printf("\n pointing : %d",ftell(infile));
                fwrite(&temp,sizeof(S),1,infile);
                //printf("\n pointing : %d\n",ftell(infile));

                fseek(infile,pos,SEEK_SET);
                if(fwrite != 0)
                    printf(" Entered succesfuly");
                else
                    printf("\n Operation failure.");

            }
            getch();

        }

    }

     if(flag == 0)
            {
                printf("\n DATA IS UP TO DATE!");
                getch();
                return;
            }
    fclose(infile);
}

//================================= SET QUESTION PAPER ======================================================

void set_paper()        //function for teacher to set paper
{

    int ch,total_q;

    do
    {
        system("cls");

        printf("\n1. Set new paper.\n2. Modify existing paper.\n3. Check currently set paper.\n0. Exit.\n\tChoice : ");
        scanf("%d",&ch);


        if(ch == 1)
        {
            int n;
            Q data;

            system("cls");
            printf("\n\n\t Enter number of questions: ");
            scanf("%d",&n);

            FILE *temp;
            temp = fopen("question_paper.dat","w");     //opening a file in w mode clears the file;

            fclose(temp);

            for(int i=0;i<n;i++)
            {
                data = get_question();
                write_to_qp(data);
            }
        }

        if(ch == 3)
        {
            total_q = read_questions();
        }

        if(ch == 2)
        {
            modify_qp();
        }

        getch();

    }while(ch != 0);

}



void write_to_qp(Q q)
{
    FILE *outfile;


    outfile = fopen ("question_paper.dat", "a+b");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    fwrite (&q, sizeof(Q), 1, outfile);

    if(fwrite != 0)
        printf("contents to question paper database written successfully !\n");
    else
        printf("error writing file !\n");

    // close file
    fclose (outfile);
}


//Gets the question from the teacher and return a structure with information pertaining to that question
Q get_question()
{
    Q q;
    printf("\n\n\t Question: ");
    fflush(stdin);
    gets(q.ques);
    printf("\nOption 1: ");
     fflush(stdin);
    gets(q.opt_1);
    printf("\nOption 2: ");
     fflush(stdin);
    gets(q.opt_2);
    printf("\nOption 3: ");
    gets(q.opt_3);
    printf("\nOption 4: ");
    gets(q.opt_4);
    printf("\nCorrect option: ");
    scanf("%d",&q.correct_opt);
    printf("\n Marks allotted to this question : ");
    scanf("%d",&q.marks);
    q.selected_opt = 0;

    return q;
}

int read_questions()
{
    FILE *infile;
    Q input;
    int flag = 0;

    int q_no = 0;

    char a;

    infile = fopen("question_paper.dat","r+b");

    if(infile == NULL)
    {
        FILE *temp;
        temp = fopen("question_paper.dat","w");     //if file doesn't exist, creates a new file;
        fclose(temp);
    }

    rewind(infile);
    while(fread(&input, sizeof(Q), 1, infile))
    {
        flag = 1;
        q_no++;
        display_qp(input,q_no);
    };

    if(flag == 0)
    {
        printf("\n Question paper not set.");
        return;
    }

    fclose(infile);

    return q_no; //returns total no. of questions in file.
}

void display_qp(Q q,int q_no)
{
    printf("\n\n Question %d: %s",q_no,q.ques);
    printf("\n\nOption 1: %s",q.opt_1);
    printf("\t\t\tOption 2: %s",q.opt_2);
    printf("\nOption 3: %s",q.opt_3);
    printf("\t\t\t\tOption 4: %s",q.opt_4);
    printf("\n\nCorrect option: %d",q.correct_opt);
    printf("\nMarks : %d",q.marks);
    printf("\n====================================================================================");
}

void modify_qp()
{
    system("cls");
    int no,total_q,q_no;
    Q data;

    do
    {
        system("cls");
        printf("\n You are about to modify the Current Question paper.\n Current question paper :\n ");
        total_q = read_questions();
        printf("\n The total no. of questions are : %d",total_q);
        //printf("%d",total_q);
        if(total_q == 0)
        {
            printf("\n Question paper doesn't exist.");
            getch();
            return;
        }

        printf("\n\n\n1. Modify question No.\n2. Add question. \n3. Delete question.\n0. Exit\n\tChoice: ");
        scanf("%d",&no);

        if(no == 1)
        {
            printf("\n Modify question no. : ");
            scanf("%d",&q_no);

            if(q_no>0 && q_no<=total_q)
            {
                FILE *infile;
                infile = fopen("question_paper.dat","r+b");

                fseek(infile,(q_no-1)*sizeof(Q),SEEK_SET);
                printf("\n Enter new Question details: \n");
                data = get_question();
                fwrite(&data,sizeof(Q),1,infile);
                fclose(infile);
            }
        }

        if(no == 2)
        {
            FILE *infile;
            infile = fopen("question_paper.dat","a+b");

            data = get_question();
            fwrite(&data,sizeof(Q),1,infile);
            fclose(infile);
        }

        if(no == 3)
        {
            system("cls");
            total_q = read_questions();
            int q_nod;
            printf("\n Question Number of the question to be delted. : ");
            scanf("%d",&q_nod);
            if(q_nod>0 && q_nod<=total_q)
            {
                FILE *infile1;
                FILE *infile2;
                infile1 = fopen("question_paper.dat","r+b");
                infile2 = fopen("Temporary_paper.dat","w+b");
                fseek(infile1,(q_nod)*sizeof(Q),SEEK_SET);
                int pos2 = ftell(infile1);
                rewind(infile1);
                while(fread(&data,sizeof(Q),1,infile1)!=NULL)
                {
                    if(pos2 != ftell(infile1))
                    {
                        fwrite(&data,sizeof(Q),1,infile2);
                    }
                    else
                    {
                        display_qp(data,q_nod);
                        getch();
                    }
                }

                char old[] = "Temporary_paper.dat";
                char newf[] = "question_paper.dat";
                fclose(infile1);
                fclose(infile2);
                remove("question_paper.dat");
                int n = rename(old,newf);
            }
        }
    }while(no != 0);

}

void reset_selected_choice()            //initialise all selected_choice variable in question paper to -1
{
    FILE *infile;
    infile = fopen("question_paper.dat","r+b");
    Q q,temp;



    while(fread(&q,sizeof(Q),1,infile))
    {
        int pos = ftell(infile);
        temp = q;
        temp.selected_opt = -1;
        fseek(infile,-sizeof(Q),SEEK_CUR);
        fwrite(&temp,sizeof(Q),1,infile);
        fseek(infile,pos,SEEK_SET);
    }

    fclose(infile);
}

int find_total_marks()          //returns the total marks the paper has been set for.
{
    int total = 0;
    Q q;

    FILE *infile = fopen("question_paper.dat","r+");

    if(infile == NULL)
    {
        printf("\n Error reading file");
        return;
    }

    else
    {
        while(fread(&q,sizeof(Q),1,infile))
        {
            total += q.marks;
        }
    }

    return total;
}

int find_total_quesions()          //returns the total marks the paper has been set for.
{
    int total = 0;
    Q q;

    FILE *infile = fopen("question_paper.dat","r+");

    if(infile == NULL)
    {
        printf("\n Error reading file");
        return;
    }

    else
    {
        while(fread(&q,sizeof(Q),1,infile))
        {
            total++;
        }
    }

    return total;
}


S take_test(S s)
{
    /*if(s.isa_marks == -1)
    {
        printf("\n ISA marks not entered.\n Kindly inform your teacher.");
        getch();
        return;
    }*/

    FILE *infile;
    infile = fopen("question_paper.dat","r+b");
    Q q;
    int q_no = 1,secured_marks = 0,flag = 0,ch;
    float effective_marks;                              //marks scored after scaling to 50.

    int total_q = find_total_quesions();

    if(infile == NULL)
    {
        printf("\n Paper not set.");
        getch();
        return;
    }

    reset_selected_choice();


    while(fread(&q,sizeof(Q),1,infile))
    {
        int pos = ftell(infile);
        flag =1;
        LABEL:
        system("cls");
        printf("\n\t\t PES UNIVERSITY\n\t\t END SEMESTER EXAMINATION\n\t\tCOMPUTER SCIENCE");
        printf("\n\nTotal No. of questions: %d",total_q);

        printf("\n\n  Question %d: %s\t\tmarks allotted: %d",q_no,q.ques,q.marks);
        printf("\n\n\t\tOption 1: %s",q.opt_1);
        printf("\t\tOption 2: %s",q.opt_2);
        printf("\n\t\tOption 3: %s",q.opt_3);
        printf("\t\tOption 4: %s",q.opt_4);
        //printf("\n Selectected opt : %d",q.selected_opt);

        //printf("\n\n\t\tYour choice : ");
        //scanf("%d",&ch);


        if(q.selected_opt == -1)
        {
            label2:

            printf("\n\n\n( 7. Next question\t\t 8. Previous question\t\t 10. Submit)");
            printf("\n\n Your choice : ");
            scanf("%d",&ch);


            if(ch == 10)
                break;


            else if(ch>=1 && ch<=4)          //if user is entering answer
            {
                Q temp;
                q.selected_opt = ch;
                temp = q;
                temp.selected_opt = q.selected_opt;
                fseek(infile,-1*sizeof(Q),SEEK_CUR);
                fwrite(&temp,sizeof(Q),1,infile);
                fseek(infile,pos,SEEK_SET);

                if(q.selected_opt == q.correct_opt)     //To assign marks
                secured_marks += q.marks;

                if(q_no == total_q)
                    goto LABEL;

                if(q_no != total_q)
                    q_no++;


            }


            else if(ch == 7)
            {
                if(q_no == total_q)
                    goto LABEL;

                else
                {
                    q_no++;
                    continue;
                }
            }


            else if(ch == 8)
            {
                if(q_no != 1)
                {
                    fseek(infile,-2*sizeof(Q),SEEK_CUR);
                    q_no -= 1;
                }

                if(q_no == 1)
                {
                    fseek(infile,0,SEEK_SET);
                }

            }

            else
            {
                printf("\n Invalid option!");
                goto label2;
            }
        }

        else
        {
            label3:

            printf("\n\n\n( 7. Next question\t 8. Previous question\t 9. Change answer\t 10.Submit)");
            printf("\n\n selected answer : %d",q.selected_opt);
            printf("\n Your choice : ");
            scanf("%d",&ch);

            if(ch == 10)
                break;

            else if(ch == 7)
            {
                if(q_no == total_q)
                    goto LABEL;
                else
                {
                    q_no++;
                    continue;
                }
            }

            else if(ch == 8)
            {
                if(q_no != 1)
                {
                    fseek(infile,-2*sizeof(Q),SEEK_CUR);
                    q_no -= 1;
                }

                if(q_no == 1)
                {
                    rewind(infile);
                }

            }

            else if(ch == 9)
            {
                printf("\n\t Your answer : ");
                scanf("%d",&ch);

                label:

                if(ch>=1 && ch<=4)
                {
                    if(q.selected_opt == q.correct_opt)     //To consider this as a fresh question attempt
                        secured_marks -= q.marks;
                    Q temp;
                    q.selected_opt = ch;
                    temp = q;
                    temp.selected_opt = q.selected_opt;
                    fseek(infile,-1*sizeof(Q),SEEK_CUR);
                    fwrite(&temp,sizeof(Q),1,infile);
                    fseek(infile,pos,SEEK_SET);

                    if(q.selected_opt == q.correct_opt)     //To assign marks
                        secured_marks += q.marks;

                    if(q_no == total_q)
                        goto LABEL;

                    if(q_no != total_q)
                        q_no++;

                    /*else if(q.selected_opt != q.correct_opt)     //To cut marks if student enter wrong answer after modifying.
                        secured_marks -= q.marks;*/

                    /*if(q_no == total_q)
                        goto LABEL;*/
                }

                else
                {
                    printf("\n Invalid option!");
                    getch();
                    goto label;
                }
            }

            else
            {
                printf("\n Invalide choice!");
                goto label3;
            }

        }


    }

    if(flag == 0)
    {
        printf("\n\n The paper has not yet been set. Please contact your teacher.");
        getch();
        return;
    }

    system("cls");
    printf("\n\t\t PES UNIVERSITY\n\t\t END SEMESTER EXAMINATION\n\t\tCOMPUTER SCIENCE");
    printf("\n\n\n You have submitted your paper");
    getch();

    system("cls");
    printf("\n\t\t PES UNIVERSITY\n\t\t END SEMESTER EXAMINATION\n\t\tCOMPUTER SCIENCE");
    printf("\n\n Marks secured = %d",secured_marks);
    getch();

    int total_marks = find_total_marks();

    effective_marks = ((float)secured_marks/total_marks)*50;
    s.esa_marks = effective_marks;

    //printf("\n\n Effective: %f",s.esa_marks);
    getch();



    fclose(infile);

    return s;
}

void enter_final_marks(S s)
{

    printf("\n Final score: %f",s.total_marks);
    S temp;
    FILE *infile = fopen("student.dat","r+");
    if(infile == NULL)
    {
        perror("");
        getch();
        return;
    }

    else
    {
        while(fread(&temp,sizeof(S),1,infile))
        {
            if(strcmp(s.SRN,temp.SRN)==0)
            {
                fseek(infile,-sizeof(S),SEEK_CUR);
                fwrite(&s,sizeof(S),1,infile);
                if(fwrite != 0)
                    printf("\nMarks noted!\n");
                else
                    printf("error writing file !\n");
                break;
            }
        }
    }

    fclose(infile);
}
void selection_sort(S *s[],int n)
{
    int i,pos,j;
    for(i = 0;i<n-1;i++)
    {
        pos = i;
        for(j = i+1;j<n;j++)
        {
            if((s[pos]->total_marks) < (s[j]->total_marks))
            // compare the roll numbers using pointers to sort the record
            pos = j;
        }
        if(pos != i)
        swap(&s[pos],&s[i]); // Swap the pointers not the structures
    }
}

void init_ptr(S s[], S *p[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        p[i] = &s[i];
    }
}

void swap(S** lhs,S** rhs)
{
    S* temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

void disp(S* p[], int n)
{
    printf("\n\t\tLEADER BOARD");
    printf("\n\n\t NAME\t\t MARKS");
    for(int i = 0; i < n; ++i)
    {
        printf("\n\t%s \t\t %.1f",p[i]->name, p[i]->total_marks);
    }

}
