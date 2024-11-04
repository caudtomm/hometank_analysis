% fpath = "\\tungsten-nas.fmi.ch\tungsten/scratch/gfriedri/caudtomm/hometank_movies/2024-10-07_13-10-55";
fext = '.mkv';
ftag = 'p';

if ~exist("side", "var")
    side = 'left';
end

% cd(fullfiletol(fpath))

%% cutting (best run on Behavior setup B main computer)
% cutMovie(pwd,'dur',600,'inForm','.mkv')

%%
files = dir(['*',ftag,'*',fext])

% order files
tmp = files;
for i_f = 1:numel(files)
    % extract part num from file name
    fspecs = getFileNameSpecs(files(i_f).name);
    pnum = str2double(extractAfter(fspecs.subject_line,'p'));
    % pnum = str2double(extractAfter(fspecs.extra,'p'));

    % store
    tmp(pnum) = files(i_f);
end
files = tmp; clear tmp

%% move to the output directory

outfolder = fullfiletol('..',side);
if ~exist(outfolder,"dir"); mkdir(outfolder); end
cd(outfolder)

%% crop videos

boundingboxes = defineBoundingBoxes(VideoReader(fullfiletol(files(1).folder, files(1).name)));

for i_f = 1:numel(files)
    thisf = fullfiletol(files(i_f).folder, files(i_f).name);
    
    tic
    outname = extractBefore(files(i_f).name,'.');
    disp(outname)
    [fishvid,ledvid,bgvid] = cropvideo(VideoReader(thisf), ...
        boundingboxes, ...
        outname);
    toc

%     [~,FishAvgInTime] = intensity_analysis(VideoReader(fishvid.Filename));
%     
%     [~,LedAvgInTime] = intensity_analysis(VideoReader(ledvid.Filename));

end

%% create summary table

FileNames = {};
NumFrames = nan(numel(files),1);
FrameRate = nan(numel(files),1);
for i_f = 1:numel(files)
    thisf = files(i_f).name;

    %load LED movie
    ledvidname = [extractBefore(thisf,'.'), '_LEDvid.avi'];
    ledvid = VideoReader(ledvidname);
    
    %store
    FileNames{i_f} = thisf;
    NumFrames(i_f) = ledvid.NumFrames;
    FrameRate(i_f) = ledvid.FrameRate;
end


summary = table(FileNames(:),NumFrames,FrameRate);

save('summary.mat',"summary")

%% extract and combine background and LED values

if ~exist("summary","var")
    load('summary.mat')
end

% -------------

BGAvgInTime = nan(sum(summary.NumFrames),1); bgcount = 1;
LedAvgInTime = nan(sum(summary.NumFrames),1); ledcount = 1;

for i_f = 1:numel(files)
    disp(num2str(i_f))

    % append background
    thisf = [extractBefore(files(i_f).name,'.'), '_backgroundvid.avi'];
    [bgmeta,~,thisval] = intensity_analysis(VideoReader(thisf));
    newcount = bgcount+length(thisval);
    BGAvgInTime(bgcount:(newcount-1)) = thisval;
    bgcount = newcount;

    % append LED
    thisf = [extractBefore(files(i_f).name,'.'), '_LEDvid.avi'];
    [ledmeta,~,thisval] = intensity_analysis(VideoReader(thisf));
    newcount = ledcount+length(thisval);
    LedAvgInTime(ledcount:(newcount-1)) = thisval;
    ledcount = newcount;
end

%fish meta
thisf = [extractBefore(files(end).name,'.'), '_fishvid.avi'];
v = VideoReader(thisf);
fishmeta.height = v.Height;
fishmeta.width = v.Width;
cropmeta.fishvid = fishmeta;
cropmeta.LEDvid = ledmeta;
cropmeta.backgroundvid = bgmeta;

save('values_raw.mat','BGAvgInTime','LedAvgInTime','cropmeta');

%plot
fs = summary.FrameRate(1); fm = fs*60;
t = 0:1/fm:length(BGAvgInTime)/fm-1/fm;
figure; plot(t,BGAvgInTime-median(BGAvgInTime))
xlabel('time [minutes]')
hold on
plot(t,LedAvgInTime-median(LedAvgInTime))
ylabel('value')
legend({'background', 'LED'})

%% get trial periods

if ~exist("BGAvgInTime","var")
    load('values_raw.mat')
end

baseline = BGAvgInTime-median(BGAvgInTime);
y = LedAvgInTime-median(LedAvgInTime)-baseline;

fs = summary.FrameRate(1); fm = fs*60;
y2 = y(movvar(y,10*fm)>0.01); % take out most of the night
y2 = y2-movmean(y2,round(100*fm)); % flatten baseline
y = y2; clear y2

% LED thresh is the 3/4-max smoothed (bg-subracted) LED value
ysmooth =movmean(y,fs); 
th = max(ysmooth) *3/4;

% plot
t = 0:1/fm:length(y)/fm-1/fm;
figure;
plot(t,y); hold on
plot(t,ysmooth);
line([0,max(xlim)],[th,th],'Color','g','LineWidth',1)
xlabel('time [minutes]')
ylabel('value')

% LED is on when?
LEDon = ysmooth>th;

% extract periods
periods = convertPeriods(LEDon);
nperiods = size(periods,1);
start_fr = periods(:,1);
stop_fr = periods(:,2);

% assign period attributions
tolerance_s = 1; % +/- val 
defaultOdorT_s = 30;
defaultFoodT_s = 1;
type = cell(nperiods,1);
len_s = diff(periods,[],2)/fs;
for i_p = 1:nperiods
    thislen_s = len_s(i_p);
    type{i_p} = 'unknown';
    if thislen_s >= defaultOdorT_s-tolerance_s && thislen_s <= defaultOdorT_s+tolerance_s
        type{i_p} = 'odor';
    elseif thislen_s >= defaultFoodT_s-tolerance_s && thislen_s <= defaultFoodT_s+tolerance_s
        type{i_p} = 'food';
    end
end
p = table(start_fr,stop_fr,len_s,type);
clear start_fr stop_fr len_s type

% create trial table
isodorperiod = strcmp(p.type,'odor');
isfoodperiod = strcmp(p.type,'food');
ntrials = sum(isodorperiod);
odor_startfr = p.start_fr(isodorperiod);
odor_stopfr = p.stop_fr(isodorperiod);
food_allstartfr = p.start_fr(isfoodperiod);
food_allstopfr = p.stop_fr(isfoodperiod);
defaultPrefoodT_s = 5;
foodlen_s = defaultFoodT_s*ones(ntrials,1); % preallocation with default val
odorlen_s = p.len_s(isodorperiod);
[food_startfr,food_stopfr] = deal(zeros(ntrials,1)); % preallocation
prefoodlen_s = defaultPrefoodT_s*ones(ntrials,1); % preallocation with default val
prefoodlen_fr = floor(prefoodlen_s*fs); % preallocation with default val
isrewarded = false(ntrials,1); % preallocation with default val
framerate = fs*ones(ntrials,1);
trials = table(odor_startfr,odor_stopfr,odorlen_s, ... % odor things
               food_startfr,food_stopfr,foodlen_s, ... % food things
               prefoodlen_fr,prefoodlen_s, ... % between odor and food
               isrewarded,framerate); % others
for i_tr = 1:ntrials
    thistrial = trials(i_tr,:);

    % is rewarded?
    tmp = (food_allstartfr - thistrial.odor_stopfr)/fs - defaultPrefoodT_s;
    thisreward = find(tmp>=-1*tolerance_s & tmp<=tolerance_s,1);
    thistrial.isrewarded = ~isempty(thisreward);

    if thistrial.isrewarded
        % assign measured reward times
        thistrial.food_startfr = food_allstartfr(thisreward);
        thistrial.food_stopfr = food_allstopfr(thisreward);
        thistrial.foodlen_s = (thistrial.food_stopfr - thistrial.food_startfr) / fs;
        thistrial.prefoodlen_fr = thistrial.food_startfr - thistrial.odor_stopfr;
        thistrial.prefoodlen_s = thistrial.prefoodlen_fr / fs;
    else
        % assign mock reward times
        thistrial.food_startfr = thistrial.odor_stopfr + thistrial.prefoodlen_fr;
        thistrial.food_stopfr = thistrial.food_startfr + floor(thistrial.foodlen_s*fs);
    end

    trials(i_tr,:) = thistrial;
end

save('trials.mat','trials')

%% make a 3D mat 'FrameAVG' [x,y,trials] ### TODO : handle reaching file limit frames (in either direction)

h = cropmeta.fishvid.height;
w = cropmeta.fishvid.width;
ntrials = size(trials,1);

odorFrameAVG = nan(h,w,ntrials);
foodFrameAVG = nan(h,w,ntrials);

for i_tr = 1:ntrials
    thistrial = trials(i_tr,:);

    % find single file coordinates
    cumFrames = cumsum(summary.NumFrames);
    fileidx = find(cumFrames >= thistrial.odor_startfr ,1);
    fname = summary.Var1(fileidx);
    fname = fname{1};
    fname = [extractBefore(fname,fext), '_fishvid'];
    fname = dir([fname,'*']).name;

    % get time intervalS of interest
    % [trial; odor; food; baseline]
    if fileidx == 1
        trial_interval = [thistrial.odor_startfr, thistrial.food_stopfr];
        odor_interval = [thistrial.odor_startfr, thistrial.odor_stopfr];
        odorT = diff(odor_interval)+1;
        food_interval = thistrial.food_startfr + [1, odorT] -1;
    else
        trial_interval = [thistrial.odor_startfr, thistrial.food_stopfr] - cumFrames(fileidx-1);
        odor_interval = [thistrial.odor_startfr, thistrial.odor_stopfr] - cumFrames(fileidx-1);
        odorT = diff(odor_interval)+1;
        food_interval = thistrial.food_startfr + [1, odorT] -1 - cumFrames(fileidx-1);
    end
    baseline_interval = trial_interval(1)-odorT*3-100 + [1, odorT*3];
    interval = [trial_interval;odor_interval;food_interval;baseline_interval];

    % get double stack of fish behavior
    v = VideoReader(fname);
    
    tic
    trialstack = getintensity(v,interval(1,:));
    odorstack = getintensity(v,interval(2,:));
    foodstack = getintensity(v,interval(3,:));
    baselinestack = getintensity(v,interval(4,:));
    toc

    odorFrameAVG(:,:,i_tr) = mean(odorstack,3)-mean(baselinestack,3);
    foodFrameAVG(:,:,i_tr) = mean(foodstack,3)-mean(baselinestack,3);

    % figure; subplot(211); title(['trial #',num2str(i_tr)])
    % imagesc(odorFrameAVG(:,:,i_tr))
    % subplot(212)
    % imagesc(foodFrameAVG(:,:,i_tr))
    
end

% plot
idx = trials.isrewarded;
figure
subplot(221)
imagesc(mean(odorFrameAVG(:,:,idx),3,'omitmissing'))
colormap('hot')
title('rewarded')
ylabel('odor')
xticks([]); yticks([])
caxis([-10 10])
subplot(222)
imagesc(mean(odorFrameAVG(:,:,~idx),3,'omitmissing'))
colormap('hot')
title('not rewarded')
xticks([]); yticks([])
caxis([-10 10])
subplot(223)
imagesc(mean(foodFrameAVG(:,:,idx),3,'omitmissing'))
colormap('hot')
ylabel('food')
xticks([]); yticks([])
caxis([-10 10])
subplot(224)
imagesc(mean(foodFrameAVG(:,:,~idx),3,'omitmissing'))
colormap('hot')
xticks([]); yticks([])
caxis([-10 10])

save('frameavgs.mat','odorFrameAVG','foodFrameAVG','-mat')