N = 200;        % number of samples (food deliveries) : 10/day
T = 1008000;    % number of possible seconds (duration of experiment, 
                % only light cycles!!) : 20 days * 14 h/day
D = 300;        % minimum inter-stamp interval [s] : 5 min

[timestamps,intervals] = generateUniformArray(N,T,D);
intervals = [round(mean(intervals)), intervals]; % add an average first delay


%% functions
function [generatedArray, diffArray] = generateUniformArray(N, T, D)
    % initialize array as fully uniform spacing
    generatedArray = linspace(0,T,N);

    % compute available space (without the D-long intervals)
    t = T - D * (N - 1);

    % randomly sampled integers between 0 and t
    tmp_array = sort(randi(t,[1,N]));

    % array of minimal distances (to be inserted)
    tmp_mindist = cumsum([0, D * ones(1,N-1)]);

    % return output array
    generatedArray = tmp_array + tmp_mindist;

    % return only the delays
    diffArray = diff(generatedArray);
end
