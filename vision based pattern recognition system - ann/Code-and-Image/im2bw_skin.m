function [ out ] = im2bw_skin( image, X, Y )

out = zeros(X, Y);
%% Segment skin on the basis of colour
for i=1:X
    for j=1:Y
        r=image(i,j,1);g=image(i,j,2);b=image(i,j,3);
        if(~(0.6<g/r<1.5&&0.6<b/r<1.5&&r<160&&(r-g)>5&&(r-b)>5))
            out(i,j) = 1;
        end 
    end 
end

end

