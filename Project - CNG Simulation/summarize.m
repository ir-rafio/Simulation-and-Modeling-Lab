clear; close all; clc;

n=10;
cngData=[]; passengerData=[];

fprintf('Loading Data ...\n');
for i=1:10
	data=csvread(strcat('trace/cng-record-day-',num2str(i),'.csv'));
	data=data(2:end, 2:6);
	cngData=[cngData; data];

	data=csvread(strcat('trace/passenger-record-day-',num2str(i),'.csv'));
	data=data(2:end, [2, 9:13]);
	passengerData=[passengerData; data];
end
fprintf('Data Loading Complete!\n');

fprintf('Generating Report ...\n');

cngData=sortrows(cngData);
passengerData(:,1)=mod(passengerData(:,1),5);
passengerData(:,1)+=5*!passengerData(:,1);
passengerData=sortrows(passengerData);

cngData1=cngData(1:20, 2:end);
cngData2=cngData(21:40, 2:end);
cngData3=cngData(41:60, 2:end);
cngData4=cngData(61:80, 2:end);
cngData5=cngData(81:100, 2:end);

passengerData1=passengerData(1:sum(cngData(1:20,2)), 2:end);
passengerData2=passengerData(1+sum(cngData(1:20,2)):sum(cngData(1:40,2)), 2:end);
passengerData3=passengerData(1+sum(cngData(1:40,2)):sum(cngData(1:60,2)), 2:end);
passengerData4=passengerData(1+sum(cngData(1:60,2)):sum(cngData(1:80,2)), 2:end);
passengerData5=passengerData(1+sum(cngData(1:80,2)):sum(cngData(1:100,2)), 2:end);

cngMean=[mean(cngData1); mean(cngData2); mean(cngData3); mean(cngData4); mean(cngData5)];
passengerMean=[mean(passengerData1); mean(passengerData2); mean(passengerData3); mean(passengerData4); mean(passengerData5)];
cngDev=[std(cngData1); std(cngData2); std(cngData3); std(cngData4); std(cngData5)];
passengerDev=[std(passengerData1); std(passengerData2); std(passengerData3); std(passengerData4); std(passengerData5)];

file=fopen('summary.csv', 'w');

fprintf(file, 'Policy,Passenger Count,,Trip Count,,Profit,,Fuel Efficiency,,');
fprintf(file, 'Queue Delay,,Halting Delay,,Road Delay,,Waiting Time,,Total Delay\n');
for i=1:columns(cngMean)+columns(passengerMean)
	fprintf(file, ',Mean,Standard Deviation');
end
fprintf(file, '\n');

for i=1:5
	fprintf(file, '%d', i);

	for j=1:columns(cngMean)
		fprintf(file, ',%f,%f', cngMean(i,j), cngDev(i,j));
	end

	for j=1:columns(passengerMean)
		fprintf(file, ',%f,%f', passengerMean(i,j), passengerDev(i,j));
	end

	fprintf(file, '\n');
end

fclose(file);
fprintf('Report Generating Completed!\n');