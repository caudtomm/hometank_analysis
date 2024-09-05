%cropping fun
function [fishvid,ledvid,bgvid] = cropvideo(v, b, outname)
    % arg 'v' is a VideoReader object
    % arg 'b' are the bounding box coords
    % arg 'outname' is typically the name of the src file without ext
    % output 'fishvid' is a VideoWriter object
    % output 'ledvid' is a VideoWriter object
    % output 'bgvid' is a VideoWriter object

    disp('cropping...')

    % Prepare the output video writers for the two cropped videos
    outputVideo1 = VideoWriter([outname,'_fishvid']);
    outputVideo2 = VideoWriter([outname,'_LEDvid']);
    outputVideo3 = VideoWriter([outname,'_backgroundvid']);
    open(outputVideo1);
    open(outputVideo2);
    open(outputVideo3);
    
    while hasFrame(v)
        frame = readFrame(v);
        % Convert to grayscale if the frame is not already grayscale
        if size(frame, 3) == 3
            frame = rgb2gray(frame);
        end
        
        % Crop the frame based on the first bounding box
        croppedFrame1 = frame(round(b.Ys(1,1):b.Ys(1,2)-1), ...
                              round(b.Xs(1,1):b.Xs(1,2)-1));
        % Crop the frame based on the second bounding box
        croppedFrame2 = frame(round(b.Ys(2,1):b.Ys(2,2)-1), ...
                              round(b.Xs(2,1):b.Xs(2,2)-1));
        % Crop the frame based on the third bounding box
        croppedFrame3 = frame(round(b.Ys(3,1):b.Ys(3,2)-1), ...
                              round(b.Xs(3,1):b.Xs(3,2)-1));
        
        % Write the cropped frames to the respective output videos
        writeVideo(outputVideo1, croppedFrame1);
        writeVideo(outputVideo2, croppedFrame2);
        writeVideo(outputVideo3, croppedFrame3);

    end
    
    % Close the output video files
    close(outputVideo1);
    close(outputVideo2);
    close(outputVideo3);

    % rename
    fishvid = outputVideo1;
    ledvid = outputVideo2;
    bgvid = outputVideo3;
end
