X=image_stitching('image1Left.jpg','image1Right.jpg');
imwrite(uint8(X),'X.jpg');

% A=image_stitching('scol_row_1.jpg','scol_row_2.jpg');
% B=image_stitching('A.jpg','scol_row_3.jpg');

% C=image_stitching('scol3_row_1_1.jpg','scol3_row_1_2.jpg');
%  imwrite(uint8(B),'B.jpg');
% D=image_stitching('C.jpg','scol3_row_1_3.jpg');
% E=image_stitching('scol3_row_2_1.jpg','scol3_row_2_2.jpg');
% F=image_stitching('E.jpg','scol3_row_2_3.jpg');
% G=image_stitching('scol3_row_3_1.jpg','scol3_row_3_2.jpg');
% H=image_stitching('G.jpg','scol3_row_3_3.jpg');
% I=image_stitching('D.jpg','F.jpg');
J=image_stitching('I.jpg','H.jpg');