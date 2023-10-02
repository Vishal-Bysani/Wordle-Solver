#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;
void get_words(char **words, int* num_words)
{
    FILE *fp;
    char *line=NULL;
    int i=0,numLines = 0;;
    size_t len = 0;
    fp=fopen("words.txt","r");
    if(!fp){ cout<<"Error opening the data file.\n"; exit(1);}

        while (getline(&line, &len, fp) != -1) {
            words[i] = strdup(line); // Allocate memory and copy line
            i++;
            
        }
    *num_words=i;
    free(line);
    fclose(fp);
}
bool is_repeated(char* word)
{
    for(int i=0;i<5;i++)
    {
        for(int j=i+1;j<5;j++)
        {
            if(word[i]==word[j])
            return true;
        }
    }
    return false;
}
bool has_character(char* word, char c)
{
    for(int i=0;i<5;i++)
    {
        if(word[i]==c)
        return true;
    }
    return false;
}
bool has_character_at(char *word, char c, int pos)
{
    return (word[pos]==c);
}
void eliminate(char* feedback,char* prev_word,int* num_words,char **words)
{
    
    for(int i=0;i<strlen(feedback);i++)
    {
        int flag=1;
        if(feedback[i]=='b')
        {
            for(int j=0;j<strlen(prev_word);j++)
            {
                if(j!=i){
                if(prev_word[j]==prev_word[i] && (feedback[j]=='g'|| feedback[j]=='y'))
                {flag=0;break;}}
            }
            if(flag!=0){
            for(int j=0;j<*num_words;j++)
            {
                if(has_character(words[j],prev_word[i]))
                {
                    for(int k=j;k<*num_words-1;k++)
                    {
                        words[k]=words[k+1];
                    }
                    *num_words=*num_words-1;
                    j--;
                }
            }
            }
            if(!flag){
                for(int j=0;j<*num_words;j++)
                {
                    if(has_character_at(words[j],prev_word[i],i))
                    {
                        for(int k=j;k<*num_words-1;k++)
                        {
                            words[k]=words[k+1];
                        }
                        *num_words=*num_words-1;
                        if(j!=0) j--;
                    }
                }
            }
        }
        else if (feedback[i]=='y')
        {
            for(int j=0;j<*num_words;j++)
            {
                if(!has_character(words[j],prev_word[i]))
                {
                    for(int k=j;k<*num_words-1;k++)
                    {
                        words[k]=words[k+1];
                    }
                    *num_words=*num_words-1;
                    if(j!=0) j--;
                }
                if(has_character_at(words[j],prev_word[i],i))
                {
                    for(int k=j;k<*num_words-1;k++)
                    {
                        words[k]=words[k+1];
                    }
                    *num_words=*num_words-1;
                    j--;
                }
            }
        }
        
        else if(feedback[i]=='g')
        {
            
            for(int j=0;j<*num_words;j++)
            {
                if(!has_character(words[j],prev_word[i]))
                {
                    for(int k=j;k<*num_words-1;k++)
                    {
                        words[k]=words[k+1];
                    }
                    *num_words=*num_words-1;
                    if(j!=0)j--;
                }
                if(!has_character_at(words[j],prev_word[i],i))
                {
                    for(int k=j;k<*num_words-1;k++)
                    {
                        words[k]=words[k+1];
                    }
                    *num_words=*num_words-1;
                    j--;
                }
            }
        }
        else{
            cout<<"Invalid Feedback\n";
        }
    }
    for(int i=0;i<*num_words;i++)
    {
        cout<<words[i]<<" ";
    }
    cout<<endl;
}
int main()
{
    char **words=new char*[2316];   //allocate space for 2315 words
    int num_words;
    get_words(words,&num_words);

    cout<<"The number of words possible now are : "<<num_words<<endl;
    cout<<"Try No. 1"<<endl;
    cout<<"drink\n";
    char *feedback=new char[5];
    cin>>feedback;

    if(!strcmp(feedback,"ggggg"))
    {
        cout<<"HURRAY!!!\n";
        delete []feedback;
        for(int i=0;i<num_words;i++)
        delete  []words[i];
        delete []words;
        return 0;
    }
    char first[]="drink";
    eliminate(feedback,first,&num_words,words);
    delete []feedback;
    string s="drink";
    const char* charPtr = s.c_str();
    for(int i=1;i<6;i++)
    {
        if(!num_words)
        {
            cout<<"No such word possible!!\n";
            return 0;
        }
        cout<<"The number of words possible now are : "<<num_words<<endl;
        cout<<"Try No. "<<(i+1)<<endl;
        if(num_words==1)
        {
            cout<<words[0]<<endl;
            cout<<"HURRAY\n";
            delete []words[0];
            delete []words;
            return 0;
        }
        int random=rand()%num_words;
        while(!strcmp(words[random],charPtr))
        {
            random=rand()%num_words;
        }
        feedback=new char[5];
        cout<<words[random]<<endl;
        cin>>feedback;
        if(!strcmp(feedback,"ggggg"))
        {
            cout<<"HURRAY!!!\n";
            delete []feedback;
            for(int i=0;i<num_words;i++)
            delete  []words[i];
            delete []words;
            return 0;
        }
        eliminate(feedback,words[random],&num_words,words);
        delete []feedback;  
        charPtr=words[random];

    }

}
