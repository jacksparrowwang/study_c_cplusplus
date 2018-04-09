#include<stdio.h>
#include"converter.h"


static int status = NULLSET;


void converter_null(FILE *ipf,FILE *opf)
{
	int c = fgetc(ipf);
	switch(c)
	{
	case '/':
		{
			int n = fgetc(ipf);
			switch(n)
			{
			case '/':
				{
					fputc('/',opf);
					fputc('/',opf);
					status = CPPSET;
				}
				break;
			case '*':
				{
					fputc('/',opf);
					fputc('/',opf);
					status = CSET;
				}
				break; 
			case EOF:
				status = EOFSET;
				break;
			default:
				fputc('/',opf);
				fputc(c,opf);
				break;
			}
		}
		break;
	case EOF:
		status = EOFSET;
		break;
	default :
		fputc(c,opf);
		break;
	}
}



void converter_c(FILE *ipf,FILE *opf)
{
	int c = fgetc(ipf);
	switch(c)
	{
	case '*':
		{
			int n = fgetc(ipf);
			switch(n)
			{
			case '/':
				{
					fputc('\n',opf);
					status = NULLSET;
				}
				break;
			default:
				ungetc(n,ipf);
				status = NULLSET;
				break;
			}
		}
		break;
	case '\n':
		fputc('\n',opf);
		fputc('/',opf);
		fputc('/',opf);
		break;
	case EOF:
		status = EOFSET;
		break;
	default :
		fputc(c,opf);
		break;
	}
}




void converter_cpp(FILE *ipf,FILE *opf)
{
	int c = fgetc(ipf);
	switch(c)
	{
	case'\n':
		fputc('\n',opf);
		status = NULLSET;
		break;
	case EOF:
		status = EOFSET;
		break;
	default :
		fputc(c,opf);
		break;
	}
}

void converter_mian()
{
	
	FILE *ipf = fopen(INPUT,"r");
	FILE *opf = fopen(OUTPUT,"w");
	if (ipf == NULL || opf == NULL)
	{
		fprintf(stderr,"open defeat\n");
		exit(1);
	}
	while(status != EOFSET)
	{
		switch(status)
		{
		case NULLSET:
			{
				converter_null(ipf,opf);
			}
			break;
		case CSET:
			{
				converter_c(ipf,opf);
			}
			break;
		case CPPSET:
			{
				converter_cpp(ipf,opf);
			}
			break;
		case EOFSET:
			break;
		default :
			break;
		}
	}
		
	fclose(ipf);
	fclose(opf);
}

