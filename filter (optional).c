#include "helpers.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            int average = (red + green + blue) / 3;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            int k = width - 1 - j;
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;
            
            for (int row = i - 1; row <= i + 1; row++)
            {
                for (int col = j - 1; col <= j + 1; col++)
                {
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        sumRed = sumRed + copy[row][col].rgbtRed;
                        sumGreen = sumGreen + copy[row][col].rgbtGreen;
                        sumBlue = sumBlue + copy[row][col].rgbtBlue;
                        count = count + 1;
                    }
                }
            }
            
            image[i][j].rgbtRed = sumRed / count;
            image[i][j].rgbtGreen = sumGreen / count;
            image[i][j].rgbtBlue = sumBlue / count;
        }
    }
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gxRed = 0;
            float gxGreen = 0;
            float gxBlue = 0;
            float gyRed = 0;
            float gyGreen = 0;
            float gyBlue = 0;
            
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int r = i + row;
                    int c = j + col;
                    if (r >= 0 && r < height && c >= 0 && c < width)
                    {
                        int red = copy[r][c].rgbtRed;
                        int green = copy[r][c].rgbtGreen;
                        int blue = copy[r][c].rgbtBlue;
                        int gxVal = gx[row + 1][col + 1];
                        int gyVal = gy[row + 1][col + 1];
                        gxRed = gxRed + red * gxVal;
                        gxGreen = gxGreen + green * gxVal;
                        gxBlue = gxBlue + blue * gxVal;
                        gyRed = gyRed + red * gyVal;
                        gyGreen = gyGreen + green * gyVal;
                        gyBlue = gyBlue + blue * gyVal;
                    }
                }
            }
            
            float r = sqrt(gxRed * gxRed + gyRed * gyRed);
            float g = sqrt(gxGreen * gxGreen + gyGreen * gyGreen);
            float b = sqrt(gxBlue * gxBlue + gyBlue * gyBlue);
            
            int finalRed = r;
            int finalGreen = g;
            int finalBlue = b;
            
            if (finalRed > 255)
                finalRed = 255;
            if (finalGreen > 255)
                finalGreen = 255;
            if (finalBlue > 255)
                finalBlue = 255;
            
            image[i][j].rgbtRed = finalRed;
            image[i][j].rgbtGreen = finalGreen;
            image[i][j].rgbtBlue = finalBlue;
        }
    }
}
