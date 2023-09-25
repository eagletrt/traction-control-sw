%% .mat to .csv control data files conversion
% This script aims to translate the data stored in the control_inputs.mat 
% and control_outs.mat files from the Vehicle model to .csv files 
% in order to use them for comparisons.

% control_inputs.mat rows are : the first one the time and then we have 
% all the inputs as in the rack on simulink

% control_outs.mat rows are: the first one the time and then 
% we have the two Tw for the two wheels as in the output rack of each control
% Notice that this procedure must be done for every control switch, 
% so for every control switch run the simulation, run this file and 
% save with the right name the new .csv file in order to not overwrite 
% then with another simulation, after you do this re-run the simulation 
% using another control switch and re- do this procedure

clc
dir = ['.' filesep 'C_code' filesep 'Simulation_output' filesep];

load([dir 'control_inputs.mat']);
load([dir 'control_outputs.mat']);
load([dir 'vel_inputs.mat']);
load([dir 'vel_outputs.mat']);

%% Procedure to export data without the time row
%If you want the time row change the number 2 in 2:end to 1

man = num2str(flags.maneuver);
ctr = num2str(flags.control_switch);
str = ['m', man, 'c', ctr];
dir = ['C_code' filesep 'Simulation_output' filesep 'Exported_csv' filesep];

fprintf("Exportation of data without the time row\n")

export = unpackStruct(vel_inputs);
writetable(export, [dir,str,'_vel_input.csv'])

export = unpackStruct(vel_outputs);
writetable(export, [dir,str,'_vel_output.csv']);

export = unpackStruct(control_inputs);
writetable(export, [dir,str,'_control_input.csv']);

export = unpackStruct(control_outputs);
writetable(export, [dir,str,'_control_output.csv']);

fprintf("Completed!\n")