%% crops the original image

function [crop_img]=crop(original, picX, picY)

%% caluclate size of the input image and make it a square image
% 
% B = imresize(A,[mrows ncols]) returns an image of size [mrows ncols]. 
% If the specified size does not produce the same aspect ratio
% as the input image has, the output image is distorted.

[x, y, z]=size(original);
if x<y
    original=imresize(original,[x x]);
else
    original=imresize(original,[y y]);
end


%% convert it into black and white

% 
% Convert image to binary image, based on threshold
% 
% Syntax
%
% BW = im2bw(I, level)
% BW = im2bw(X, map, level)
% BW = im2bw(RGB, level)
%
% Description
% 
% BW = im2bw(I, level) converts the grayscale image I to a binary image. 
% The output image BW replaces all pixels in the input image with luminance 
% greater than level with the value 1 (white) and replaces all other pixels 
% with the value 0 (black). Specify level in the range [0,1]. This range is 
% relative to the signal levels possible for the image's class. Therefore, 
% a level value of 0.5 is midway between black and white, regardless of class. 
% To compute the level argument, you can use the function graythresh. 
% If you do not specify level, im2bw uses the value 0.5.
% 
% BW = im2bw(X, map, level) converts the indexed image X with colormap map to a binary image.
% 
% BW = im2bw(RGB, level) converts the truecolor image RGB to a binary image.
% 
% If the input image is not a grayscale image, im2bw converts the input image to grayscale, and then converts this grayscale image to binary by thresholding.

bw1=double(im2bw(original,0.5));




%% add noise on it and then remove it.


% 'salt & pepper' - On and off pixels
% J = imnoise(I,'salt & pepper',d) adds salt and pepper noise to the image 
% I, where d is the noise, pixels defaults density, density. This affects approximately 
% d*numel(I) pixels. The default for d is 0.05.

J = imnoise(bw1,'salt & pepper',0.0001);
J = -1 * (J - 1);

%% 2-D median filtering

% B = medfilt2(A, [m n]) performs median filtering of the matrix A in two dimensions.
% Each output pixel contains the median value in the m-by-n neighborhood around the 
% corresponding pixel in the input image. medfilt2 pads the image with 0s on the edges, 
% so the median values for the points within [m n]/2 of the edges might appear distorted.
% 
% Median filtering is a nonlinear operation often used in image processing to reduce 
% "salt and pepper" noise. A median filter is more effective than convolution when 
% the goal is to simultaneously reduce noise and preserve edges.

L = medfilt2(J,[5 5]);




%% calculate the size of filtered image
[x, y, z]=size(L);

% figure('name','black and white');
% imshow(L);

%% create variables to store the coordinates of the 1st white pixel from each
% direction

top=0;
toppos_b=0;
left=0;
leftpos_a=0;
right=0;
rightpos_a=0;
bottom=0;
bottompos_b=0;

%% calculate 1st white pixel from each direction
for i=1:x-1
    for j=1:y-1
        if top==0 && L(i,j)==1 
            toppos_b=i;
            top=1;
        end
        if left==0 && L(j,i)==1 
            leftpos_a=i;
            left=1;
        end
        if right==0 && L(j,x-i)==1 
            rightpos_a=x-i;
            right=1;
        end
        if bottom==0 && L(x-i,j)==1 
            bottompos_b=x-i;
            bottom=1;
        end
        if top==1 && left ==1 && right==1 && bottom==1
            break
        end
    end
end

%% crop original image to remove extra background

% I2 = imcrop(I, rect) crops the image I. rect is a four-element position 
% vector[xmin ymin width height] that specifies the size and position of the crop rectangle. 

crop_img=imcrop(original,[leftpos_a toppos_b rightpos_a-leftpos_a bottompos_b-toppos_b]);

%% B = imresize (A, [mrow mcol])
% Scales the image A to be of size mrowxmcol. 

crop_img=imresize(crop_img,[picX picY]);