
function [meta, avgIntensity, avgInTime] = intensity_analysis(v)
    % arg 'v' is a VideoReader object or filename

    tic
    if isstring(v) || ischar(v)
        stack = loadTiffStack(v);
    else
        stack = getintensity(v);
    end
    toc


    [imHeight,imWidth,numFrames] = size(stack);
    meta.height = imHeight;
    meta.width = imWidth;


    % ################## PLOT AVG FRAME
    
    %[imHeight,imWidth,numFrames] = size(fishstack);
    avgIntensity = mean(stack,3);
    
    % % Plot Z-Project (AVG intensity)
    % figure;
    % imagesc(avgIntensity);
    % title('Average Intensity');
    
    % ################## PLOT AVG INTENSITY IN TIME
    
    avgInTime = zeros(1, numFrames);
    
    for k = 1:numFrames
        avgInTime(k) = mean(stack(:, :, k), 'all');
    end
    
    % % Plot the average intensity over time
    % figure;
    % plot(avgInTime);
    % xlabel('Frame Number');
    % ylabel('Average Intensity');
    % title('Average Frame Intensity Over Time');
    

end

