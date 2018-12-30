#include "planning/map/Image.h"


Image::Image()
{
}


Image::~Image()
{
}

#define  MAXLENGTH 2000
#define  MAXHIGH 2000
//#define  MAXLENGTH 1000
bool Image::Readpgm(string fileName) {
      FILE *filePointer;    /* for file buffer */
      char line[MAXLENGTH]; /* for character input from file */
      int maximumValue = 0; /* max value from header */
      int binary;           /* flag to indicate if file is binary (P5)*/
      long numberRead = 0;  /* counter for number of pixels read */
      long i,j;             /* (i,j) for loops */
      int test,temp;        /* for detecting EOF(test) and temp storage */

      /* Open the file, return an error if necessary. */
      if ((filePointer = fopen(fileName.c_str(),"r")) == NULL) {
	   printf ("ERROR: cannot open file\n\n");
	   fclose (filePointer);
	   return 0;
      }
    
      /* Initialize columnsidth, and height */
      cols = 0;
	  rows =0;

      /* Check the file signature ("Magic Numbers" P2 and P5); skip comments
       * and blank lines (CR with no spaces before it).*/
      fgets (line,MAXLENGTH,filePointer);
      while (line[0]=='#' || line[0]=='\n') fgets (line,MAXLENGTH,filePointer);
      if (line[0]=='P' && (line[1]=='2')) {
	   binary = 0;
	 /*   printf ("\nFile Format: P2\n"); */
      }
      else if (line[0]=='P' && (line[1]=='5')) {
	   binary = 1;
	  /*  printf ("\nFORMAT: P5\n"); */
      }
      else {
	   printf ("ERROR: incorrect file format\n\n");
	   fclose (filePointer);
	   return 0;
      }          

      /* Input the width, height and maximum value, skip comments and blank
       * lines. */
      fgets (line,MAXLENGTH,filePointer);
      while (line[0]=='#' || line[0]=='\n') fgets (line,MAXLENGTH,filePointer);
      sscanf (line,"%d %d",&cols,&rows);

      fgets (line,MAXLENGTH,filePointer);
      while (line[0]=='#' || line[0]=='\n') fgets(line,MAXLENGTH,filePointer);
      sscanf (line,"%d",&maximumValue);

      /* display specifications and return an error if h,w, or
      *  maximum value is illegal.*/
   /*    printf("Rows: %ld   Columns: %ld\n",*rows,*cols); */
/*       printf("Maximum value: %d\n\n",maximumValue); */

      if (cols<1 ||rows<1 || maximumValue<0){
	   printf ("ERROR: invalid file specifications (cols/rows/max value)\n\n");
	   fclose (filePointer);
	   return 0;
      }

	  unsigned char image[MAXLENGTH][MAXHIGH];
      /* Read in the data for binary (P5) or ascii (P2) PGM formats   */
      if (binary) {
	   for (i = 0; i < rows; i++) {
	        numberRead += fread((void *)&(image[i][0]),
		  sizeof(unsigned char),cols,filePointer); 
		if (feof(filePointer)) break;
	   }
      }
      else {
	   for (i= 0; i < rows; i++) {
	        for (j =0; j < cols; j++) { 
	             test = fscanf (filePointer,"%d",&temp);
		     if (test == EOF) break;
		     image[i][j] = (unsigned char)temp;

		     numberRead++;
		}
		if (test == EOF) break;
	   }
      } 
 
   /*    printf ("  Rows * Columns = %ld\n",(*rows)*(*cols)); */
/*       printf ("  Number of pixels read = %ld\n\n",numberRead); */

      /* Insure the number of pixels read is at least the
       *   number indicated by w*h.
       * If not, return an error message, but proceed */
      if (numberRead < rows*cols) {
	   printf ("ERROR: fewer pixels than rows*cols indicates\n\n");
      }
     
	for (i= 0; i < rows; i++) {
		for (j =0; j < cols; j++) { 
			data_R[i][j] = image[i][j];
			data_G[i][j] = image[i][j];
			data_B[i][j] = image[i][j];
			if (data_R[i][j] + data_G[i ][j] + data_B[i ][j]< 400)
				data[i ][j] = 0;
			else
				data[i ][j] = 1;
		}
	}

      /* close the file and return 1 indicating success */
      fclose (filePointer);
      return 1;
}






bool Image::Read24BMP(string strFileName)
{
	if (strFileName.size()==0)	return 0;

	BITMAPFILEHEADER	FileHeader;
	BITMAPINFOHEADER	InfoHeader;
	FILE*				fp;
	BYTE			    *pCur;
	BYTE				tmp;
	int					ImgSize, Patch, Extend, i;

	if ((fp = fopen(strFileName.c_str(), "rb")) == NULL) return 0;
	if (fread((void *)&FileHeader, 1, 14, fp) != 14){ fclose(fp); return 0; }
	if (fread((void *)&InfoHeader, 1, 40, fp) != 40){ fclose(fp); return 0; }
	if (FileHeader.bfOffBits < 54){ fclose(fp); return 0; }
	if (InfoHeader.biBitCount != 24){ fclose(fp); return 0; }

	cols = (int)InfoHeader.biWidth;
	rows = (int)InfoHeader.biHeight;
	if(cols*rows == 0){
		ROS_ERROR("Image::Read24BMP: Image is null!");
		return 0;
	}
	Patch = 3 * cols;
	ImgSize = Patch*rows;
	fseek(fp, FileHeader.bfOffBits, SEEK_SET);

	if ((pBmpBuf = new BYTE[ImgSize]) == NULL){ fclose(fp); return 0; }

	Extend = (cols * 3 + 3) / 4 * 4 - cols * 3;
	for (pCur = pBmpBuf + ImgSize - Patch;
		pCur >= pBmpBuf;
		pCur -= Patch)
	{
		if (fread((void *)pCur, 1, Patch, fp) != uint(Patch))
		{
			delete[]pBmpBuf; fclose(fp); return 0;
		}
		for (i = 0; i < Extend; i++)
		if (fread(&tmp, 1, 1, fp) != 1)
		{
			delete[]pBmpBuf; fclose(fp); return 0;
		}
	}
	fclose(fp);
	bmpbuf_to_vec();
	return 1;
}

bool Image::Write24BMP(string strFileName)
{
	vec_to_bmpbuf();
	if (rows*cols == 0) return false;
	BYTE *pImg = pBmpBuf;

	if (strFileName.size()==0)	return false;
	if (!pImg)			return false;

	BITMAPFILEHEADER	FileHeader;
	BITMAPINFOHEADER	InfoHeader;
	FILE				*fp;
	BYTE				*pCur;
	int					ImgSize, Patch, Extend, i;

	Patch = cols * 3;
	ImgSize = (cols + 3) / 4 * 4 * rows;

	if ((fp = fopen(strFileName.c_str(), "wb+")) == NULL) return false;
	FileHeader.bfType = ((WORD)('M' << 8) | 'B');
	FileHeader.bfOffBits = 54; // sizeof(FileHeader)+sizeof(InfoHeader)
	FileHeader.bfSize = FileHeader.bfOffBits + ImgSize;
	FileHeader.bfReserved1 = 0;
	FileHeader.bfReserved2 = 0;

	InfoHeader.biSize = 40;
	InfoHeader.biWidth = cols;
	InfoHeader.biHeight = rows;
	InfoHeader.biPlanes = 1;
	InfoHeader.biBitCount = 24;
	InfoHeader.biCompression = 0;
	InfoHeader.biSizeImage = ImgSize;
	InfoHeader.biXPelsPerMeter = 0;
	InfoHeader.biYPelsPerMeter = 0;
	InfoHeader.biClrUsed = 0;
	InfoHeader.biClrImportant = 0;

	if (fwrite((void *)&FileHeader, 1, 14, fp) != 14)
	{
		fclose(fp); remove(strFileName.c_str()); return false;
	}
	if (fwrite((void *)&InfoHeader, 1, 40, fp) != 40)
	{
		fclose(fp); remove(strFileName.c_str()); return false;
	}

	Extend = (cols * 3 + 3) / 4 * 4 - cols * 3;
	for (pCur = pImg + (rows - 1)*Patch;
		pCur >= pImg;
		pCur -= Patch)
	{
		if (fwrite((void *)pCur, 1, Patch, fp) != uint(Patch))
		{
			fclose(fp); remove(strFileName.c_str()); return false;
		}

		for (i = 0; i < Extend; i++)
		if (fwrite((void *)(pCur + Patch - 3), 1, 1, fp) != 1)
		{
			fclose(fp); remove(strFileName.c_str()); return false;
		}

	}
	fclose(fp);
	return true;
}


void Image::bmpbuf_to_vec(){
	//resize
	data_R.resize(rows);
	for (auto &vec : data_R)
		vec.resize(cols);
	data_G.resize(rows);
	for (auto &vec : data_G)
		vec.resize(cols);
	data_B.resize(rows);
	for (auto &vec : data_B)
		vec.resize(cols);
	data.resize(rows);
	for (auto &vec : data)
		vec.resize(cols);

	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			data_R[i ][j] = pBmpBuf[j * 3 + 2 + cols*i * 3];
			data_G[i ][j] = pBmpBuf[j * 3 + 1 + cols *i * 3];
			data_B[i ][j] = pBmpBuf[j * 3 + cols *i * 3];
			if (data_R[i ][j] + data_G[i ][j] + data_B[i ][j]< 400)
				data[i ][j] = 0;
			else
				data[i ][j] = 1;
		}
	}
}


void Image::vec_to_bmpbuf(){
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			pBmpBuf[j * 3 + 2 + cols*i * 3] = data_R[i ][j];
			pBmpBuf[j * 3 + 1 + cols *i * 3] = data_G[i ][j];
			pBmpBuf[j * 3 + cols *i * 3] = data_B[i ][j];
		}
	}
}

void Image::setcolor(int x, int y, char color){
	switch (color)
	{
		//��
	case 'r': data_R[x][y] = 255;
			  data_G[x][y] = 0;
			  data_B[x][y] = 0;
			  break;
	//��
	case 'g': data_R[x][y] = 0;
			  data_G[x][y] = 255;
		      data_B[x][y] = 0;
			  break;
	//��
	case 'b': data_R[x][y] = 0;
		      data_G[x][y] = 0;
		      data_B[x][y] = 255;
			  break;
			  //��
	case 'W': data_R[x][y] = 255;
		      data_G[x][y] = 255;
		      data_B[x][y] = 255;
			  break;
			  //��
	case 'B': data_R[x][y] = 0;
		      data_G[x][y] = 0;
		      data_B[x][y] = 0;
			  break;
			  //��
	case 'G': data_R[x][y] = 100;
			  data_G[x][y] = 100;
		      data_B[x][y] = 100;
		      break;
	default:
		break;
	}

}


void Image::compressionBMP(Image& img, double scale){
	//����ͼ��ߴ�
	img.rows = round(scale*rows);
	img.cols = round(scale*cols);
	
	//����pBmpBuf
	int lineByte2 = (img.cols * 3 + 3) / 4 * 4;
	img.pBmpBuf = new unsigned char[lineByte2 * img.rows];///Ϊ���ź�ͼ�����洢�ռ�
	int pre_i, pre_j, after_i, after_j;//����ǰ���Ӧ�����ص�����
	for (int i = 0; i<img.rows; i++)
	{
		for (int j = 0; j<img.cols; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				after_i = i;
				after_j = j;
				pre_i = min(rows, (int)round(after_i / scale));/////ȡ������ֵ����Ϊ�����ڽ���ֵ������ȡ������
				pre_j = min(cols, (int)round(after_j / scale));
				//��ԭͼ��Χ��
				*(img.pBmpBuf + i * lineByte2 + j * 3 + k) = *(pBmpBuf + pre_i * cols * 3 + pre_j * 3 + k);
			}
		}
	}
	//�������ؾ���
	img.bmpbuf_to_vec();
}