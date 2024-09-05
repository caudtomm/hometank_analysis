% convert videos to double mat stacks
function stack = getintensity(v,interval)
    % arg 'v' is a VideoReader object
    % (opt) arg 'interval' is double[1,2] indicating start and end frame

    disp('converting to double stack...')

    % Get video properties
    numFrames = v.NumFrames;
    vidHeight = v.Height;
    vidWidth = v.Width;
    
    % Specify start and end frame
    if exist('interval','var') && ~isempty(interval)
        startfr = interval(1);
        stopfr = interval(2);
    else
        startfr = 1;
        stopfr = numFrames;
    end
    numOutFrames = stopfr-startfr+1;

    % Initialize a matrix to hold the intensity values
    stack = zeros(vidHeight, vidWidth, numOutFrames);
    
    % Read each frame and store its intensity values
    for k = startfr:stopfr
        frame = read(v, k);
        % Convert to grayscale if not already
        if size(frame, 3) == 3
            frame = rgb2gray(frame);
        end
        stack(:, :, k-startfr+1) = frame;
    end

end
