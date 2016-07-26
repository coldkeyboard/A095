#include "ShowImage.h"

void ShowImage(char *filename)
{
  unsigned char *mydata;
  printf("hello Jimmy~~\n");
 	BITMAPINFOHEADER bitmapInfoHeader;
	mydata = LoadBitmapFile(filename, &bitmapInfoHeader);
  Picture_out(mydata);
}

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader) 
{ 
    FILE *filePtr; //our file pointer 
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header 
    unsigned char *bitmapImage;  //store image data 
    int imageIdx=0;  //image index counter 
     
    //open filename in read binary mode 
    filePtr = fopen(filename,"rb"); 
    if (filePtr == NULL) { 
		printf("Couldn't open file\n"); 
    	return NULL; 
	  }
	 
    //read the bitmap file header 
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);  
    printf("File Type:%x\n", bitmapFileHeader.bfType);
    printf("File Size:%d\n", bitmapFileHeader.bfSize);
    printf("Reserved1:%d\n", bitmapFileHeader.bfReserved1);
    printf("Reserved2:%d\n", bitmapFileHeader.bfReserved2);
    printf("Offset Bit:%d\n", bitmapFileHeader.bOffBits);

    //verify that this is a bmp file by check bitmap id 
    if (bitmapFileHeader.bfType !=0x4D42) 
    { 
		printf("Expected 0x4d42, found: %x\n", bitmapFileHeader.bfType); 
		printf("File is not a bmp\n"); 
 		fclose(filePtr); 
        return NULL; 
    } 
 
    //read the bitmap info header                                 //應該不需要由要外部輸入參數，可和bitmapFileHeader一樣寫在此函數裡 
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);  //此處為指標，不需要"&" 
    printf("Info Size:%d\n", bitmapInfoHeader->biSize);           //此處為指標，用"->" 
    printf("Width:%d\n", bitmapInfoHeader->biWidth);
    printf("Height:%d\n", bitmapInfoHeader->biHeight);    
    printf("Planes:%d\n", bitmapInfoHeader->biPlanes);
    printf("BitCount:%d\n", bitmapInfoHeader->biBitCount);
    printf("Compression:%d\n", bitmapInfoHeader->biCompression);
    printf("SizeImage:%d\n", bitmapInfoHeader->biSizeImage);
    printf("XPelsPerMeter:%d\n", bitmapInfoHeader->biXPelsPerMeter);
    printf("YPelsPerMeter:%d\n", bitmapInfoHeader->biYPelsPerMeter);
    printf("ClrUsed:%d\n", bitmapInfoHeader->biClrUsed);
    printf("ClrImportant:%d\n", bitmapInfoHeader->biClrImportant); 
    printf("54Palette:%x\n", bitmapInfoHeader->biPalette);  
	  printf("58:%x\n", bitmapInfoHeader->t1);
	  printf("62:%x\n", bitmapInfoHeader->t2);
    printf("size of BFH:%d\n", sizeof(BITMAPFILEHEADER));
    printf("size of BIH:%d\n", sizeof(BITMAPINFOHEADER));
    //move file point to the begging of bitmap data 
    fseek(filePtr, bitmapFileHeader.bOffBits, SEEK_SET); 
	
    //allocate enough memory for the bitmap image data 
    //bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);  //有些圖檔biSizeImage為0，故改用bfSize 
    bitmapImage = (unsigned char*)malloc(bitmapFileHeader.bfSize); 

   //verify memory allocation 
    if (!bitmapImage) 
    { 
		printf("Error 2\n"); 
        free(bitmapImage); 
        fclose(filePtr); 
        return NULL; 
    } 
	 
    //read in the bitmap image data 
    //fread(bitmapImage,bitmapInfoHeader->biSizeImage,1,filePtr); //有些圖檔biSizeImage為0，故改用bfSize
    fread(bitmapImage,bitmapFileHeader.bfSize,1,filePtr); 
	  printf("bitmapImage[0]]:%x\n", bitmapImage[0]);   //用來和62的第一個位元(最右邊)比對，以確認抓的值是對的，注意圖的原點不一定在左上角 
    //make sure bitmap image data was read 
    if (bitmapImage == NULL) 
    { 
		printf("Error 3\n"); 
        fclose(filePtr); 
        return NULL; 
    } 	 
  	//for(imageIdx=0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3){ 
  	//	tft_writeColor(bitmapImage[imageIdx+2], bitmapImage[imageIdx+1], bitmapImage[imageIdx]); 
  	//} 
    //close file and return bitmap iamge data 
    fclose(filePtr); 
    return bitmapImage; 
} 


//--------------------------------------------------- Copy from Ritdisplay.
void Picture_out(unsigned char *mydata)     
{
  unsigned char *ptr;
  unsigned char i,j,k,Column_HighByte,Column_LowByte,Low_byte,buffer;

  ptr=mydata;
  k=0;
  for(i=0;i<128;i++)
  {
  
    for(j=0;j<8;j++)
    {
      buffer=*ptr;
      Low_byte=0;
    //--------------(Byte Translate-------------------------
      if (((buffer & 0x80)>>7) == 1)
      {Low_byte=Low_byte | 0x01;}
    
      if (((buffer & 0x40)>>6) == 1)
      {Low_byte=Low_byte | 0x02;}
    
      if (((buffer & 0x20)>>5) == 1)
      {Low_byte=Low_byte | 0x04;}
    
      if (((buffer & 0x10)>>4) == 1)
      {Low_byte=Low_byte | 0x08;}
    
      if (((buffer & 0x08)>>3) == 1)
      {Low_byte=Low_byte | 0x10;}
    
      if (((buffer & 0x04)>>2) == 1)
      {Low_byte=Low_byte | 0x20;}
    
      if (((buffer & 0x02)>>1) == 1)
      {Low_byte=Low_byte | 0x40;}
    
      if (((buffer & 0x01)>>0) == 1)
      {Low_byte=Low_byte | 0x80;}
    //--------------Byte Translate)-------------------------
    //--------------(Column Translate-----------------------
      Column_HighByte=i+0x00>>4;
      Column_HighByte=Column_HighByte & 0x0f;
      Column_HighByte=Column_HighByte | 0x10;
    
      Column_LowByte=i+0x00;
      Column_LowByte=Column_LowByte & 0x0f;
      //--------------Column Translate)-----------------------
      commandOutput(0xb0+j);
      commandOutput(Column_LowByte);
      commandOutput(Column_HighByte);
      dataOutput(Low_byte);
      ptr=ptr+1;

    }
  }
}