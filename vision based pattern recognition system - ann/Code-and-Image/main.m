%% Vision based system for gesture recognition using neural networks course project

% Contants
normX = 50;
normY = 50;
NUM_NET = 30;

%   x - input data.
%   t - target data.

x = []; t = [];
for s = 1:5
    for r = 1:20
        file_name = strcat(num2str(s) , ' (' , num2str(r) , ')' , '.jpg');
        y1 = crop(imread(file_name), normX, normY);
        %figure
        %imshow(y1)
        y11 = im2bw_skin(y1, normX, normY);
        y1 = y11;
        figure
        imshow(y1)

        %%
        temp1 = [];
        for i=1:normX
            for j = 1:normY
                temp1 = [temp1 y1(i,j)];
            end
        end

        y1 = 2*temp1' - 1;

        x = [x; y1'];
        t1 = zeros(1,5);
        t1(s) = 1;
        t = [t; t1];
    end
end
x = x';
t = t';

%% Creating a Pattern Recognition Network
 net = patternnet(NUM_NET);
% net = newff(minmax(x), [2500 NUM_NET 5], {'purelin' 'tansig' 'purelin'}, 'trainscg');
 %net.trainParam.epochs                 20
% Choosing Input and Output Pre/Post-Processing Functions

%   General Data Preprocessing
%  
%     fixunknowns        - Processes matrix rows with unknown values.
%     mapminmax          - Map matrix row minimum and maximum values to [-1 1].
%     mapstd             - Map matrix row means and deviations to standard values.
%     processpca         - Processes rows of matrix with principal component analysis.
%     removeconstantrows - Remove matrix rows with constant values.
%     removerows         - Remove matrix rows with specified indices.


net.inputs{1}.processFcns = {'removeconstantrows','mapminmax'};
net.outputs{2}.processFcns = {'removeconstantrows','mapminmax'};


% Seting up Division of Data for Training, Validation, Testing

net.divideFcn = 'dividerand';  % Divide data randomly
net.divideMode = 'sample';  % Divide up every sample
net.divideParam.trainRatio = 55/100;
net.divideParam.valRatio = 25/100;
net.divideParam.testRatio = 20/100;

%% assigning the training function

%  To change a neural network's training algorithm set the net.trainFcn
%   property to the name of the corresponding function.  For example, to use
%   the scaled conjugate gradient backprop training algorithm:
%  
%     net.trainFcn = 'trainscg';
%  
%   Backpropagation training functions that use Jacobian derivatives
%  
%     These algorithms can be faster but require more memory than gradient
%     backpropation.  They are also not supported on GPU hardware.
%  
%     trainlm   - Levenberg-Marquardt backpropagation.
%     trainbr   - Bayesian Regulation backpropagation.
%  
%   Backpropagation training functions that use gradient derivatives
%  
%     These algorithms may not be as fast as Jacobian backpropagation.
%     They are supported on GPU hardware with the Parallel Computing Toolbox.
%  
%     trainbfg  - BFGS quasi-Newton backpropagation.
%     trainscg  - Scaled conjugate gradient backpropagation.
%  
%   Supervised weight/bias training functions
%  
%     trainb    - Batch training with weight & bias learning rules.
%     trainc    - Cyclical order weight/bias training.
%  
%   Unsupervised weight/bias training functions
%  
%     trainbu   - Unsupervised batch training with weight & bias learning rules.
%     trainru   - Unsupervised random order weight/bias training.





%     Neural Network Toolbox
%     Function Approximation and Nonlinear Regression
% 
% trainscg
% 
% Scaled conjugate gradient backpropagation
% 
% Syntax
% 
% net.trainFcn = 'trainscg'
% [net,tr] = train(net,...)
% Description
% 
% trainscg is a network training function that updates weight and bias values according to the scaled conjugate gradient method.
% 
% net.trainFcn = 'trainscg'
% 
% [net,tr] = train(net,...)
% 
% Training occurs according to trainscg's training parameters, shown here with their default values:
% net.trainParam.epochs                 100			Maximum number of epochs to train
% net.trainParam.show					25			Epochs between displays (NaN for no displays)
% net.trainParam.showCommandLine		0			Generate command-line output
% net.trainParam.showWindow             1			Show training GUI
% net.trainParam.goal					0			Performance goal
% net.trainParam.time					inf			Maximum time to train in seconds
% net.trainParam.min_grad				1e-6		Minimum performance gradient
% net.trainParam.max_fail				5			Maximum validation failures
% net.trainParam.sigma                  5.0e-5		Determine change in weight for second derivative approximation
% net.trainParam.lambda                 5.0e-7		Parameter for regulating the indefiniteness of the Hessian
% 
% Network Use
% 
% You can create a standard network that uses trainscg with feedforwardnet or cascadeforwardnet. To prepare a custom network to be trained with trainscg,
% 
%     Set net.trainFcn to 'trainscg'. This sets net.trainParam to trainscg's default parameters.
% 
%     Set net.trainParam properties to desired values.
% 
% In either case, calling train with the resulting network trains the network with trainscg.
% 
% Examples
% 
% Here is a problem consisting of inputs p and targets t to be solved with a network.
% 
% p = [0 1 2 3 4 5];
% t = [0 0 0 1 1 1];
% 
% A two-layer feed-forward network with two hidden neurons and this training function is created.
% 
% net = feedforwardnet(2,'trainscg');
% 
% Here the network is trained and retested.
% 
% net = train(net,p,t);
% a = net(p)



net.trainFcn = 'trainscg';  % Scaled conjugate gradient backpropagation.

% net.layers{2}.transferFcn = 'trainscg';
% net.biasConnect(1) = 0;
% net.biasConnect(2) = 0;

%% Choosing the Performance Function

%   Neural Network Performance Functions.
%  
%     mae - Mean absolute error performance function.
%     mse - Mean squared error performance function.
%     sae - Sum absolute error performance function.
%     sse - Sum squared error performance function.


net.performFcn = 'mse';  % Mean squared error


%% Train the Network
net = train(net,x,t);



%% In case manual assignment of layers, activation functions etc.
% 
% 	   
% newff
% 
% Create a feed-forward backpropagation network
% 
% Syntax
% 
% net = newff
% 
% net = newff(PR,[S1 S2...SNl],{TF1 TF2...TFNl},BTF,BLF,PF)
% 
%
% net = newff(minmax(pn), [5 5 1], {'tansig' 'tansig' 'purelin'}, 'trainlm');
%
%
% Description
% 
% net = newff creates a new network with a dialog box.
% 
% newff(PR,[S1 S2...SNl],{TF1 TF2...TFNl},BTF,BLF,PF) takes,
% 
%     PR - R x 2 matrix of min and max values for R input elements.
% 
%     Si - Size of ith layer, for Nl layers.
% 
%     TFi - Transfer function of ith layer, default = 'tansig'.
% 
%     BTF - Backpropagation network training function, default = 'traingdx'.
% 
%     BLF - Backpropagation weight/bias learning function, default = 'learngdm'.
% 
%     PF - Performance function, default = 'mse'.
% 
% and returns an N layer feed-forward backprop network.
% 
% The transfer functions TFi can be any differentiable transfer function such 
% as tansig, logsig, or purelin.
% 
% The training function BTF can be any of the backprop training functions 
% such as trainlm, trainbfg, trainrp, traingd, etc.
% Caution: trainlm is the default training function because it is very fast, 
% but it requires a lot of memory to run. If you get an "out-of-memory" error when training try doing one of these:
% 
%     Slow trainlm training, but reduce memory requirements by setting net.trainParam.mem_reduc to 2 or more. (See help trainlm.)
%     Use trainbfg, which is slower but more memory-efficient than trainlm.
%     Use trainrp, which is slower but more memory-efficient than trainbfg. 
% 
% The learning function BLF can be either of the backpropagation learning functions such as learngd or learngdm.
% 
% The performance function can be any of the differentiable performance functions such as mse or msereg.
% 
% Examples
% 
% Here is a problem consisting of inputs P and targets T that we would like to solve with a network.
% 
%     P = [0 1 2 3 4 5 6 7 8 9 10];
%     T = [0 1 2 3 4 3 2 1 2 3 4];
% 
% Here a two-layer feed-forward network is created. The network's input ranges 
% from [0 to 10]. The first layer has five tansig neurons, the second layer has 
% one purelin neuron. The trainlm network training function is to be used.
% 
%     net = newff([0 10],[5 1],{'tansig' 'purelin'});
% 
% Here the network is simulated and its output plotted against the targets.
% 
%     Y = sim(net,P);
%     plot(P,T,P,Y,'o')
% 
% Here the network is trained for 50 epochs. Again the network's output is plotted.
% 
%     net.trainParam.epochs = 50;
%     net = train(net,P,T);
%     Y = sim(net,P);
%     plot(P,T,P,Y,'o')
% 
% Algorithm
% 
% Feed-forward networks consist of Nl layers using the dotprod weight function, 
% netsum net input function, and the specified transfer functions.
% 
% The first layer has weights coming from the input. Each subsequent layer 
% has a weight coming from the previous layer. All layers have biases. The last layer is the network output.
% 
% Each layer's weights and biases are initialized with initnw.
% 
% Adaption is done with trains, which updates weights with the specified learning function. 
% Training is done with the specified training function. Performance is measured according to the specified performance function.
% 





%% View the Network
view(net)

%% Test the Network
y = net(x);
perf = perform(net,t,y);


%% Displaying the classes

% Convert vectors to indices
% 
% Syntax
% 
%     ind = vec2ind(vec)
% 
% Description
% 
% ind2vec and vec2ind allow indices to be represented either by themselves or as vectors containing a 1 in the row of the index they represent.
% 
% vec2ind(vec) takes one argument,
% 
%     vec - Matrix of vectors, each containing a single 1.
% 
% and returns the indices of the 1's.
% 
% Examples
% 
% Here four vectors (each containing only one "1" element) are defined and the indices of the 1's are found.
% 
%     vec = [1 0 0 0; 0 0 1 0; 0 1 0 1]
%     ind = vec2ind(vec)
% 


classes = vec2ind(y)
disp('Training done');