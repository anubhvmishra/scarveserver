#include <iostream> 
#include <opencv2/opencv.hpp> 
using namespace cv; 
using namespace std; 


void getMinCostPathWidth(int* arr, double** energy, int height, int width)
{
    long double** minCost=new long double*[height];
    for (int i=0;i<height;i++) 
    {
        minCost[i] = new long double[width];
    }

    for(int j=0;j<width;j++)
    {
        minCost[0][j]=energy[0][j];
    }
    for(int i=1;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            double mini=minCost[i-1][j];
            if(j==0)
            {
                if(minCost[i-1][j+1]<mini)
                {
                    mini=minCost[i-1][j+1];
                }
            }
            else if(j==width-1)
            {
                if(minCost[i-1][j-1]<mini)
                {
                    mini=minCost[i-1][j-1];
                }
            }
            else
            {
                if(minCost[i-1][j+1]<mini)
                {
                    mini=minCost[i-1][j+1];
                }
                if(minCost[i-1][j-1]<mini)
                {
                    mini=minCost[i-1][j-1];
                }
            }
            minCost[i][j]=energy[i][j]+mini;
        }
    }

    long double mini=minCost[height-1][0];
    int minColIndex=0;
    for(int j=0;j<width;j++)
    {
        if(minCost[height-1][j]<mini)
        {
            mini=minCost[height-1][j];
            minColIndex=j;
        }
    }
    arr[height-1]=minColIndex;
    for(int i=height-2;i>=0;i--)
    {
        long double mini=minCost[i][minColIndex];
        int updatedMinCol=minColIndex;
        if(minColIndex==0)
        {
            if(minCost[i][minColIndex+1]<mini)
            {
                mini=minCost[i][minColIndex+1];
                updatedMinCol=minColIndex+1;
            }
        }
        else if(minColIndex==width-1)
        {
            if(minCost[i][minColIndex-1]<mini)
            {
                mini=minCost[i][minColIndex-1];
                updatedMinCol=minColIndex-1;
            }
        }
        else
        {
            if(minCost[i][minColIndex-1]<mini)
            {
                mini=minCost[i][minColIndex-1];
                updatedMinCol=minColIndex-1;
            }
            if(minCost[i][minColIndex+1]<mini)
            {
                mini=minCost[i][minColIndex+1];
                updatedMinCol=minColIndex+1;
            }
        }
        minColIndex=updatedMinCol;
        arr[i]=minColIndex;
    }

    for (int i=0;i<height;i++) 
    {
        delete[] minCost[i];
    }
    delete[] minCost;
}


void getMinCostPathHeight(int* arr, double** energy, int height, int width)
{
    long double** minCost=new long double*[height];
    for (int i=0;i<height;i++) 
    {
        minCost[i] = new long double[width];
    }

    for(int i=0;i<height;i++)
    {
        minCost[i][0]=energy[i][0];
    }

    for(int j=1;j<width;j++)
    {
        for(int i=0;i<height;i++)
        {
            double mini=minCost[i][j-1];
            if(i==0)
            {
                if(minCost[i+1][j-1]<mini)
                {
                    mini=minCost[i+1][j-1];
                }
            }
            else if(i==height-1)
            {
                if(minCost[i-1][j-1]<mini)
                {
                    mini=minCost[i-1][j-1];
                }
            }
            else
            {
                if(minCost[i+1][j-1]<mini)
                {
                    mini=minCost[i+1][j-1];
                }
                if(minCost[i-1][j-1]<mini)
                {
                    mini=minCost[i-1][j-1];
                }
            }
            minCost[i][j]=energy[i][j]+mini;
        }
    }

    long double mini=minCost[0][width-1];
    int minRowIndex=0;
    for(int i=0;i<height;i++)
    {
        if(minCost[i][width-1]<mini)
        {
            mini=minCost[i][width-1];
            minRowIndex=i;
        }
    }

    arr[width-1]=minRowIndex;

    for(int j=width-2;j>=0;j--)
    {
        long double mini=minCost[minRowIndex][j];
        int updatedMinRow=minRowIndex;
        if(minRowIndex==0)
        {
            if(minCost[minRowIndex+1][j]<mini)
            {
                mini=minCost[minRowIndex+1][j];
                updatedMinRow=minRowIndex+1;
            }
        }
        else if(minRowIndex==height-1)
        {
            if(minCost[minRowIndex-1][j]<mini)
            {
                mini=minCost[minRowIndex-1][j];
                updatedMinRow=minRowIndex-1;
            }
        }
        else
        {
            if(minCost[minRowIndex-1][j]<mini)
            {
                mini=minCost[minRowIndex-1][j];
                updatedMinRow=minRowIndex-1;
            }
            if(minCost[minRowIndex+1][j]<mini)
            {
                mini=minCost[minRowIndex+1][j];
                updatedMinRow=minRowIndex+1;
            }
        }
        minRowIndex=updatedMinRow;
        arr[j]=minRowIndex;
    }
    for (int i=0;i<height;i++) 
    {
        delete[] minCost[i];
    }
    delete[] minCost;

}


void createEnergyMatrix(double** energyMat, int height, int width, int channels,unsigned char* pixels)
{
    for (int i=0;i<height;i++) 
        {
            for (int j=0;j<width;j++) 
            {
                int prevI=i-1;
                int prevJ=j-1;
                int nextI=i+1;
                int nextJ=j+1;
                if(i==0)
                {
                    prevI=height-1;

                }
                if(j==0)
                {
                    prevJ=width-1;

                }
                if(i==height-1)
                {
                    nextI=0;
                }
                if(j==width-1)
                {
                    nextJ=0;
                }

                int index=(i*width+j)*channels;     //multiply by 3 since 3 values per cell

                int prevXIndex=(i*width+prevJ)*channels;
                int nextXIndex=(i*width+nextJ)*channels;

                int prevYIndex=(prevI*width+j)*channels;
                int nextYIndex=(nextI*width+j)*channels;

                long long Bx=abs(pixels[prevXIndex]-pixels[nextXIndex]);
                long long Gx=abs(pixels[prevXIndex+1]-pixels[nextXIndex+1]);
                long long Rx=abs(pixels[prevXIndex+2]-pixels[nextXIndex+2]);

                long long By=abs(pixels[prevYIndex]-pixels[nextYIndex]);
                long long Gy=abs(pixels[prevYIndex+1]-pixels[nextYIndex+1]);
                long long Ry=abs(pixels[prevYIndex+2]-pixels[nextYIndex+2]);

                long long gradX=Bx*Bx + Gx*Gx + Rx*Rx;
                long long gradY=By*By + Gy*Gy + Ry*Ry;

                double energy=sqrt(gradX+gradY);

                energyMat[i][j]=energy;

            }
        }
}



string getFilename(string path)
{

	int lastIndexOf=path.find_last_of('/');
	if(lastIndexOf==-1)
	{
		return path.c_str();
	}
	string fileName=path.substr(lastIndexOf+1,path.size()-lastIndexOf-1);
	return fileName.c_str();
}

int main(int argc, char** argv)
{
    if (argc != 5) {
        cout << "Usage: " << argv[0] << " <input_image> <output_image> <n_of_cols_to_reduce> <n_of_rows_to_reduce>\n";
        return 1;
    }
    string filePath = argv[1];
    string outputFilePath = argv[2];
    int nOfColsToReduce = stoi(argv[3]);
    int nOfRowsToReduce = stoi(argv[4]);

    Mat image = imread(filePath, IMREAD_COLOR);
    Mat Outimage;

    if (image.empty()) {
        cout << "Could not open or find the image\n";
        return 1;
    }

    unsigned char* pixels = image.data;       // 0 to 255
    int width = image.cols;
    int height = image.rows;
    int channels = image.channels();

    cout << "Image size is width x height " << width << " x " << height << "\n";

    if (nOfColsToReduce > width) {
        cout << "Please enter width lesser or equal to the original image\n";
        return 1;
    }

    if (nOfRowsToReduce > height) {
        cout << "Please enter height lesser or equal to the original image\n";
        return 1;
    }

    double** energyMat = new double*[height];
    for (int i = 0; i < height; i++) {
        energyMat[i] = new double[width];
    }

    double mini;
    int minColIndex, minRowIndex;
    Mat updatedImage(height, width - 1, image.type());
    unsigned char* updated = updatedImage.data;

    int removeCols[height];
    for (int colsReduced = 0; colsReduced < nOfColsToReduce; colsReduced++) {
        if (colsReduced % 25 == 0) {
            createEnergyMatrix(energyMat, height, width, channels, pixels);
        }
        Mat updatedImage(height, width - 1, image.type());
        updated = updatedImage.data;
        getMinCostPathWidth(removeCols, energyMat, height, width);

        for (int i = 0; i < height; i++) {
            minColIndex = removeCols[i];

            for (int j = minColIndex; j < width - 1; j++) {
                energyMat[i][j] = energyMat[i][j + 1];
            }

            for (int j = 0; j < minColIndex; j++) {
                int index = (i * width + j) * channels;
                int index2 = (i * (width - 1) + j) * channels;    // updated has one less cell every row
                updated[index2] = pixels[index];
                updated[index2 + 1] = pixels[index + 1];
                updated[index2 + 2] = pixels[index + 2];
            }
            for (int j = minColIndex; j < width - 1; j++) {
                int index = (i * (width - 1) + j) * channels;
                int index2 = (i * width + j + 1) * channels;
                updated[index] = pixels[index2];
                updated[index + 1] = pixels[index2 + 1];
                updated[index + 2] = pixels[index2 + 2];
            }
            int index = (i * width + minColIndex) * 3;
            pixels[index] = 0;
            pixels[index + 1] = 0;
            pixels[index + 2] = 255;
        }
        width--;
        image = updatedImage;
        pixels = image.data;
    }

    int removeRows[width];

    for(int rowsReduced=0;rowsReduced<nOfRowsToReduce;rowsReduced++)
        {
            if(rowsReduced%25==0)
            {
                createEnergyMatrix(energyMat,height,width,channels,pixels);
            }
            Mat updatedImage(height-1,width,image.type());
            updated=updatedImage.data;
            getMinCostPathHeight(removeRows,energyMat,height,width);

            for(int j=0;j<width;j++)
            {
                minRowIndex=removeRows[j];

                for (int i=minRowIndex;i<height-1;i++) 
                {
                    energyMat[i][j]=energyMat[i+1][j];
                }

                for (int i=0;i<minRowIndex;i++) 
                {
                    int index=(i*width+j)*channels;
                    updated[index]=pixels[index];
                    updated[index+1]=pixels[index+1];
                    updated[index+2]=pixels[index+2];
                }

                for (int i=minRowIndex;i<height-1;i++) 
                {
                    int index=(i*width+j)*channels;
                    int index2=((i+1)*width+j)*channels;
                    updated[index]=pixels[index2];
                    updated[index+1]=pixels[index2+1];
                    updated[index+2]=pixels[index2+2];
                }
                int index=(minRowIndex*width + j)*3;
                pixels[index]=0;      
                pixels[index+1]=0;
                pixels[index+2]=255;

            }
            
            height--;
            image=updatedImage;
            pixels=image.data;
        }

    string nameOfOutput = outputFilePath;
    bool checkIfWritten = imwrite(nameOfOutput, image);
    if (checkIfWritten == false) {
        cout << "Failed to save the image. Please try again\n";
    }

    for (int i = 0; i < height; i++) {
        delete[] energyMat[i];
    }
    delete[] energyMat;

    return 0;
}

