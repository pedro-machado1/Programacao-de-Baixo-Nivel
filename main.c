#include <stdio.h>
#include <stdlib.h>

int main(){ 

    char document[50];
    printf("Digite o nome para a imagem que deseja editar ");
    scanf("%s",document);
    printf("%s\n", document);
    
    FILE *fp;
    
  	fp = fopen(document,"r");
	if(fp==NULL){
		printf("Erro ao abrir o arquivo!");
        return 0;
		}
  	char tipoImg[3];

  	int i, j, linha, coluna, val, r, g, b;
  	
  	fscanf(fp, "%s", tipoImg);  
  	printf("%s\n", tipoImg);
  	
  	fscanf(fp, "%d %d", &coluna, &linha);   
  	printf("%d %d\n", coluna, linha);
 //   if (coluna < 400 || linha < 400){
   //     printf("imagem é muito pequena");
    //    return 0;
   // }

      int **matriz;
 
      matriz = malloc (linha * sizeof (int *));
      
      for (int i = 0; i < linha; ++i)
      {
         matriz[i] = malloc (coluna * sizeof (int));
      }
      
    struct RGB
{
    int R, G, B;
};

    struct RGB **matrizRGB = (struct RGB **)malloc(linha * sizeof(struct RGB *));
    for (i = 0; i < linha; i++) 
    {
        matrizRGB[i] = (struct RGB *)malloc(coluna * sizeof(struct RGB));    
    }

    struct RGB **matrizinversa = (struct RGB **)malloc(coluna * sizeof(struct RGB *));
    for (i = 0; i < coluna; i++) 
    {
        matrizinversa[i] = (struct RGB *)malloc(linha * sizeof(struct RGB));    
    }

    
  	
  	fscanf(fp, "%d", &val);  
  	printf("%d\n", val);

    int opcao;
    printf("Digite 1 se quer gerar uma imagem tons de cinza\n Digite 2 se que gerar uma imagem negatina \n Digite 3 se quer gerar uma imagem raio-x \nDigite 4 se quer gerar uma imagem envelhecida (sepia)\n Digite 5 se quer gerar uma imagem 90 graus \n Digite 6 se que rotacionar a imagem em 180 graus \n");
    printf("Digite o numero da opcao que voce deseja: ");
    scanf("%i", &opcao);
    switch (opcao)
    {
        case 1:
            for(j=0; j<linha; j++)
            {
                for(i=0; i<coluna; i++)
                {
                    fscanf(fp, "%d %d %d", &r, &g, &b);
                    
		  	        matriz[j][i] = (r*0.299)+(g*0.587)+(b*0.114);
                }
            }

            fclose(fp);
    
            FILE *fp_novo = fopen ("arquivoModificado.ppm", "w");
            
            fprintf (fp_novo, "P2\n");
            fprintf (fp_novo, "%d %d\n", coluna, linha);
            fprintf (fp_novo, "%d\n", val);
    
            for(j=0; j<linha; j++)
            {
                    for(i=0; i<coluna; i++)
                    {  	
                        fprintf(fp_novo, "%d\n" , matriz[j][i]);
                    }
            }
            fclose(fp_novo); 
            break;
        case 2:
                for(j=0; j<linha; j++)
                {
                    for(i=0; i<coluna; i++)
                    {
                        fscanf(fp, "%d %d %d", &r, &g, &b);
                        matrizRGB[j][i].R = 255 -r;
                        matrizRGB[j][i].G = 255 -g;
                        matrizRGB[j][i].B = 255 -b;
                    }
                }

                fclose(fp);
        
                FILE *fp_novo2 = fopen ("arquivoModificado.ppm", "w");

                fprintf (fp_novo2, "P3\n");
                fprintf (fp_novo2, "%d %d\n", coluna, linha);
                fprintf (fp_novo2, "%d\n", val);

                for (i = 0; i < linha; i++) 
                {
                    for (j = 0; j < coluna; j++) 
                    {
                    fprintf(fp_novo2, "%d %d %d ", matrizRGB[i][j].R, matrizRGB[i][j].G, matrizRGB[i][j].B);
                    }
                    fprintf(fp_novo2, "\n");
                }
                fclose(fp_novo2);

                break;
        case 3:
        for(j=0; j<linha; j++)
        {
            for(i=0; i<coluna; i++)
            {
                fscanf(fp, "%d %d %d", &r, &g, &b);
                
                matriz[j][i] = (r*0.299)+(g*0.587)+(b*0.114);
                matriz[j][i] = fmin(pow(matriz[j][i], 1.5), 255);
            }
        }

        fclose(fp);

        FILE *fp_novo3 = fopen ("arquivoModificado.ppm", "w");
        
        fprintf (fp_novo3, "P2\n");
        fprintf (fp_novo3, "%d %d\n", coluna, linha);
        fprintf (fp_novo3, "%d\n", val);

        for(j=0; j<linha; j++)
        {
                for(i=0; i<coluna; i++)
                {  	
                    fprintf(fp_novo3, "%d\n" , matriz[j][i]);
                }
        }
        fclose(fp_novo3); 
        break;
        case 4:
            for(j=0; j<linha; j++)
            {
                for(i=0; i<coluna; i++)
                {
                    fscanf(fp, "%d %d %d", &r, &g, &b);
                    
                    matrizRGB[j][i].R = (r*(1+ 0.1));
                    matrizRGB[j][i].G = (g*(1+0.1));
                    matrizRGB[j][i].B = (b*(1 - 0.1));
                    matrizRGB[j][i].R = fmin(matrizRGB[j][i].R + 10, 255);
                    matrizRGB[j][i].G = fmin(matrizRGB[j][i].G + 10, 255);
                    matrizRGB[j][i].B = fmax(matrizRGB[j][i].B - 10, 0);
                }
            }
            
            fclose(fp);
           
            FILE *fp_novo4 = fopen ("arquivoModificado.ppm", "w");

            fprintf (fp_novo4, "P3\n");
            fprintf (fp_novo4, "%d %d\n", coluna, linha);
            fprintf (fp_novo4, "%d\n", val);

            for (i = 0; i < linha; i++) 
            {
                for (j = 0; j < coluna; j++) 
                {
                fprintf(fp_novo4, "%d %d %d ", matrizRGB[i][j].R, matrizRGB[i][j].G, matrizRGB[i][j].B);
                }
                fprintf(fp_novo4, "\n");
            }
            fclose(fp_novo4);


            break;
        case 5:
            
            
            for(j=0; j<linha; j++)
            {
                for(i=0; i<coluna; i++)
                {
                    fscanf(fp, "%d %d %d", &r, &g, &b);
                    matrizRGB[j][i].R = r;
                    matrizRGB[j][i].G = g;
                    matrizRGB[j][i].B = b;
                }
            }

            fclose(fp);
    
            FILE *fp_novo5 = fopen ("arquivoModificado.ppm", "w");
            fprintf (fp_novo5, "P3\n");
            fprintf (fp_novo5, "%d %d\n", linha, coluna);
            fprintf (fp_novo5, "%d\n", val);

            for (i = 0; i < coluna; i++) 
            {
                for (j = 0; j <linha; j++) 
                {
                    fprintf(fp_novo5, "%d %d %d ", matrizRGB[j][i].R, matrizRGB[j][i].G, matrizRGB[j][i].B);
                }
                fprintf(fp_novo5, "\n");
            }
            fclose(fp_novo5);

            break;          
        case 6:
            for(j=linha-1; j>=0; j--){
                for(i=0; i<coluna; i++){
                    fscanf(fp, "%d %d %d", &r, &g, &b);
                    matrizRGB[j][i].R = r;
                    matrizRGB[j][i].G = g;
                    matrizRGB[j][i].B = b;
                }
            }
            fclose(fp);
    
            FILE *fp_novo6 = fopen ("arquivoModificado.ppm", "w");
            fprintf (fp_novo6, "P3\n");
            fprintf (fp_novo6, "%d %d\n", coluna, linha);
            fprintf (fp_novo6, "%d\n", val);

            for (i = 0; i < linha; i++) 
            {
                for (j = 0; j <coluna; j++) 
                {
                    fprintf(fp_novo6, "%d %d %d ", matrizRGB[i][j].R, matrizRGB[i][j].G, matrizRGB[i][j].B);
                }
                fprintf(fp_novo6, "\n");
            }
            fclose(fp_novo6);

            break;
        default:    
            printf("por favor coloque um numero valido");
            return 1;
            break;
    }
    return 0;
    
}

