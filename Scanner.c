#include <stdio.h>
#include <stdlib.h>

struct SignatureOptions
{
    unsigned int offset;
    unsigned char Bytecode[8];
    char FileName[127];

};
int StrCounts (int *StrCount, char *name)
{
    if(StrCount==NULL)
    {
        return 1;
    }
    if (name==NULL)
    {
        return 2;
    }
    *StrCount=0;
    char StrChar [255];
    FILE *f;
    f = fopen(name,"r");
    if (f==NULL)
    {
        return 3;
    }
    while (fgets(StrChar,255,f)!=NULL)
    {
        (*StrCount)++;
    }
    if (fclose(f)!=0)
    {
        return 4;
    }
return 0;
}

int StructReadSignature (struct SignatureOptions *a, char *name, int StrCount)
{
    if (a==NULL)
    {
        return 1;
    }
    if (name==NULL)
    {
        return 2;
    }
    if (StrCount==0)
    {
        return 3;
    }
    FILE *f;
    f = fopen(name,"rb");
    if (f==NULL)
    {
        return 4;
    }
    for (int i=0;i<StrCount;i++)
    {
        if (fscanf(f,"%x",&a[i].offset)!=1)
        {
            return 5;
        }
        for (int j=0;j<8;j++)
        {
            if(fscanf(f,"%hhx",&a[i].Bytecode[j])!=1)
            {
                return 6;
            }
        }
        if(fscanf(f,"%s",a[i].FileName)!=1)
        {
            return 7;
        }
    }
    if (fclose(f)!=0)
    {
        return 8;
    }
    return 0;
}

int MZFunction (char *name, int *MZ)
{
  if (name==NULL)
  {
      return 1;
  }
  if (MZ==NULL)
  {
      return 2;
  }
  FILE *f;
  *MZ=0;
  unsigned char c[2];
  f = fopen(name,"rb");
  if (f==NULL)
  {
      return 3;
  }
  if (fread(c, sizeof(unsigned char),2,f)!=2)
  {
      return 4;
  }
  if ((c[0]=='M')&&(c[1]=='Z'))
  {
      (*MZ)++;
  }
  if (fclose(f)!=0)
  {
      return 5;
  }
  return 0;
}
int ExeStructReadSignature (struct SignatureOptions *a, char *exename, int StrCount, int *memoryS,int *off)
{
    if (a==NULL)
    {
        return 1;
    }
    if (exename==NULL)
    {
        return 2;
    }
    if (StrCount==0)
    {
        return 3;
    }
    if (memoryS==NULL)
    {
        return 4;
    }
    if (off==NULL)
    {
        return 5;
    }
    int k;
    *memoryS=0;
    unsigned char Bytes[8];
    FILE *f;
    f = fopen(exename,"rb");
    if (f==NULL)
    {
        return 6;
    }
    for (int i=0;i<StrCount;i++)
    {
        k=0;
        if(fseek(f,a[i].offset,SEEK_SET)!=0)
        {
            return 7;
        }
        if (fread(Bytes,sizeof(Bytes[0]),8,f)!=8)
        {
            return 8;
        }
        *memoryS=0;
        for (int j=0;j<8;j++)
        {
            if (a[i].Bytecode[j]!=Bytes[j])
            {
                continue;
            }
            else
            {
                k++;
            }
        }
        if (k==8)
            {
                (*memoryS)=k;
                (*off)=i;
                if (fclose(f)!=0)
                {
                    return 9;
                }
                return 0;
                break;
            }
            else
            {
                (*memoryS)=0;
            }
    }
    if (fclose(f)!=0)
    {
        return 9;
    }
    return 0;
}


int main()
{
    if (printf("Welcome to signature scanner\n\nTo use scanner you need to do some steps\n\n")<0)
    {
        return 1;
    }
    if (printf("1. Plug in the file with signatures\n\nExample: Signature.txt\n\n2. Write the way to the file you want to check\n\nExample: C:\\\\steam.exe\n\n3. Wait for result\n\n")<0)
    {
        return 2;
    }
    int StrCount,CheckCounts,CheckRS,CheckMZ,MZ,CheckESRS, memoryS,off;
    char FileName [255], ExeName[255];
    if (printf("Please, plug in the file with signatures (a.txt)\n\n")<0)
    {
        return 3;
    }
    if(scanf("%s",FileName)!=1)
    {
        return 4;
    }
    CheckCounts = StrCounts(&StrCount,FileName);
    if (CheckCounts!=0)
    {
        switch(CheckCounts)
        {
        case 1:
            {
                if(printf("StrCounts function: invalid counter\n\n")<0)
                {
                    return 5;
                }
                break;
            }
        case 2:
            {
                if (printf("StrCounts function: invalid array\n\n")<0)
                {
                    return 6;
                }
                break;
            }
        case 3:
            {
                if (printf("StrCounts function: invalid file name\n\n")<0)
                {
                    return 7;
                }
                break;
            }
        case 4:
            {
                if(printf("StrCounts function: file was not closed\n\n")<0)
                {
                    return 8;
                }
                break;
            }
        default:
            {
                if(printf("StrCounts function: Unknown error\n\n")<0)
                {
                    return 9;
                }
                break;
            }
        }
    }
    if (CheckCounts==0)
    {
    struct SignatureOptions *a;
    a = (struct SignatureOptions*)malloc(StrCount*sizeof(a[0]));
    if(a==NULL)
    {
        return 10;
    }
    CheckRS = StructReadSignature(a,FileName,StrCount);
    if(CheckRS!=0)
    {
        switch (CheckRS)
        {
        case 1:
            {
                if (printf("StructReadSignature function: invalid struct\n\n")<0)
                {
                    return 11;
                }
                break;
            }
        case 2:
            {
                if (printf("StructReadSignature function: invalid array\n\n")<0)
                {
                    return 12;
                }
                break;
            }
        case 3:
            {
                if (printf("StructReadSignature function: invalid counter\n\n")<0)
                {
                    return 13;
                }
                break;
            }
        case 4:
            {
                if (printf("StructReadSignature function: invalid file name\n\n")<0)
                {
                    return 14;
                }
                break;
            }
        case 5:
            {
                if (printf("StructReadSignature function: invalid scanning\n\n")<0)
                {
                    return 15;
                }
                break;
            }
        case 6:
            {
                if (printf("StructReadSignature function: invalid scanning\n\n")<0)
                {
                    return 16;
                }
                break;
            }
        case 7:
            {
                if(printf("StructReadSignature function: invalid scanning\n\n")<0)
                {
                    return 17;
                }
                break;
            }
        case 8:
            {
                if(printf("StructReadSignature function: file was not closed\n\n")<0)
                {
                    return 18;
                }
                break;
            }
        default:
            {
                if(printf("StructReadSignature function: Unknown error\n\n")<0)
                {
                    return 19;
                }
                break;
            }
        }
    }
    if (printf("\nPlease write the filepath to your checking file (Example: C:\\\\Windows\\\\System32\\\\calc.exe)\n\n")<0)
    {
        return 20;
    }
    if(scanf("%s",ExeName)!=1)
    {
        return 21;
    }
    CheckMZ = MZFunction(ExeName,&MZ);
    if (CheckMZ!=0)
    {
        switch(CheckMZ)
        {
        case 1:
            {
                if(printf("MZFunction: invalid array\n\n")<0)
                {
                    return 22;
                }
                break;
            }
        case 2:
            {
                if(printf("MZFunction: invalid counter\n\n")<0)
                {
                    return 23;
                }
                break;
            }
        case 3:
            {
                if(printf("\nMZFunction: invalid file name\n\n")<0)
                {
                    return 24;
                }
                break;
            }
        case 4:
            {
                if(printf("MZFunction: invalid scanning\n\n")<0)
                {
                    return 25;
                }
                break;
            }
        case 5:
            {
                if(printf("MZFunction: file was not closed\n\n")<0)
                {
                    return 26;
                }
                break;
            }
        default:
            {
                if(printf("MZFunction: Unknown error\n\n")<0)
                {
                    return 27;
                }
                break;
            }
        }
    }
    switch (MZ)
    {
    case 1:
        {
            if(printf("\nFile access enabled\n\n")<0)
            {
                return 28;
            }
            break;
        }
    case 0:
        {
            if(printf("\nNo file access, file has not got an exe format or has invalid name\n\n")<0)
            {
                return 29;
            }
            break;
        }
    default:
        {
            if(printf("Unknown error\n\n")<0)
            {
                return 30;
            }
            break;
        }
    }
    if (MZ==1)
    {
    CheckESRS = ExeStructReadSignature(a,ExeName,StrCount,&memoryS,&off);
    if (CheckESRS!=0)
    {
    switch (CheckESRS)
    {
    case 1:
        {
            if (printf("ExeStructReadSignature: invalid structure\n\n")<0)
            {
                return 31;
            }
            break;
        }
        case 2:
        {
            if (printf("ExeStructReadSignature: invalid array\n\n")<0)
            {
                return 32;
            }
            break;
        }
        case 3:
            {
                if(printf("ExeStructReadSignature: invalid counter, signature file is empty\n\n")<0)
                {
                    return 33;
                }
                break;
            }
        case 4:
            {
                if (printf("ExeStructReadSignature: invalid counter\n\n")<0)
                {
                    return 34;
                }
                break;
            }
        case 5:
            {
                if (printf("ExeStructReadSignature: invalid counter\n\n")<0)
                {
                    return 35;
                }
                break;
            }
        case 6:
            {
                if (printf("ExeStructReadSignature: EXE file name is incorrect\n\n")<0)
                {
                    return 36;
                }
                break;
            }
        case 7:
            {
                if(printf("ExeStructReadSignature: invalid offset\n\n")<0)
                {
                    return 37;
                }
                break;
            }
        case 8:
            {
                if (printf("ExeStructReadSignature: invalid scanning\n\n")<0)
                {
                    return 38;
                }
                break;
            }
        case 9:
            {
                if (printf("ExeStructReadSignature: file was not closed\n\n")<0)
                {
                    return 39;
                }
                break;
            }
        default:
            {
                if (printf("ExeStructReadSignature: unknown error\n\n")<0)
                {
                    return 40;
                }
                break;
            }
    }
    }
    switch(memoryS)
    {
    case 8:
        {
            if(printf("Signature found\n\n")<0)
            {
                return 41;
            }
            if (printf("%s",a[off].FileName)<0)
            {
                return 42;
            }
            break;
        }
    default:
        {
            if(printf("EXE file is clear!\n\n")<0)
            {
                return 43;
            }
            break;
        }
       }
      }
      free(a);
     }
    return 0;
}
