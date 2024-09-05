
% define bounding boxes for fish and led
function b = defineBoundingBoxes(v)
    % arg 'v' is a VideoReader object
    % outputs 'Xs' and 'Ys' in struct 'b' are double mats, format:
    %   [box1_min, box1_max; ... ; boxN_min, boxN_max]

    % Read the first frame of the video to select the ROIs
    firstFrame = readFrame(v);
    
    % Display the first frame and select the first ROI
    imshow(firstFrame); title('select tank water (2x click it to confirm)')
    h1 = imrect;
    position1 = wait(h1); % Wait for the user to double-click to confirm selection
    
    % Select the second ROI
    title('select LED (2x click it to confirm)')
    h2 = imrect;
    position2 = wait(h2); % Wait for the user to double-click to confirm selection

    % Select the third ROI
    title('select background (2x click it to confirm)')
    h3 = imrect;
    position3 = wait(h3); % Wait for the user to double-click to confirm selection

    % close image
    close
    
    % Position format: [xmin ymin width height]
    xmin1 = position1(1); ymin1 = position1(2);
    width1 = position1(3); height1 = position1(4);
    
    xmin2 = position2(1); ymin2 = position2(2);
    width2 = position2(3); height2 = position2(4);

    xmin3 = position3(1); ymin3 = position3(2);
    width3 = position3(3); height3 = position3(4);

    % Calculate the bounding box coordinates for both ROIs
    xmax1 = xmin1 + width1;
    ymax1 = ymin1 + height1;
    
    xmax2 = xmin2 + width2;
    ymax2 = ymin2 + height2;

    xmax3 = xmin3 + width3;
    ymax3 = ymin3 + height3;
    
    % store
    b.Xs = [xmin1, xmax1 ; xmin2, xmax2 ; xmin3, xmax3];
    b.Ys = [ymin1, ymax1 ; ymin2, ymax2 ; ymin3, ymax3];

end

