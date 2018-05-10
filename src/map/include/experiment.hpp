

std::vector<std::string> getTranscript(std::vector<Position> c ){
	std::vector<std::string> temp;
	for(int i=0;i<c.size();i++){
		temp.push_back(c[i].transcriptId);	
	}
 return temp;
}

void experiment(std::string filename, std::vector<Position> Contig2Transcript[]) {
	std::cout<<"in experiment"<<endl;
	std::string line;
	ifstream myfile;
	//string inputFileName = "D:\\spring 18\\523\\small.bacterial.genome.fixed_31_fixed_pufferized.gfa";
	string outputFileName = "output.txt";
	ofstream outputFile;
	outputFile.open(outputFileName);
	myfile.open(filename);
	unordered_map <int, int> contigInfo;
	//map<int, string> pathInfo;
	std::vector<int> output;
	int n = 1000;
	while (getline(myfile, line))
	{
		if (line[0] == 'S') {
			int wordNum = 0;
			int contigId;
			string contig;
			std::string delimiter = "\t";
			size_t firstPos = line.find(delimiter);
			size_t lastPos = line.find_last_of(delimiter);
			contigId = stoi(line.substr(firstPos + 1, lastPos));
			//contig = line.substr(lastPos + 1);
			contig = line.substr(lastPos);
			//cout << "contigid and its length inserted in map " << contigId << "   " << contig.length() << "\n";
			contigInfo.insert(pair <int, int>(contigId, contig.length()));
		}
	}
	
	myfile.close();
	myfile.clear();
	myfile.open(filename);
	while (getline(myfile, line)) {
		if (line[0] == 'P') {
			std::string path;
			//std::vector<Position> temp;
			std::size_t found = line.find_last_of("\t");
			path = line.substr(found + 1);
			//cout << "processing path " << path << "\n";
			std::vector<int> paths;
			std::size_t foundFirst = line.find("\t");
			std::string pathid = line.substr(foundFirst, found - foundFirst);
			std::string delimiter = ",";
			size_t pos = 0;
			size_t newPos = 0;
			std::string token;
			int i = 0;
			int flag = 0;
			//std::vector<int> output;
			std::vector<std::string> transcripts;
			while ((newPos = path.find(delimiter, pos)) != std::string::npos) {
				//cout << "pos  " << pos << "newpos  " << newPos << "\n";
				token = path.substr(pos, newPos - pos);
				//cout << "token " << token.substr(0, token.length() - 1) << '\n';
				pos = newPos + 1;
				paths.push_back(stoi(token.substr(0, token.length() - 1)));
			}
			token = path.substr(pos, newPos - pos);
			paths.push_back(stoi(token.substr(0, token.length() - 1)));
			int remaining = n;
			std::vector<int> validContigs;
			int skipLength = 0;
			
			for (unsigned i = 0; i < paths.size(); i++) {
				if(flag != 1)
					validContigs.clear();
				remaining = remaining - contigInfo.find(paths[i])->second;
				validContigs.push_back(paths[i]);
				flag = 0;
				if (remaining <= 0) {
					std::vector<std::string> first=getTranscript(Contig2Transcript[contigIdmap[std::to_string(validContigs[0])]]);
					std::cout<<"FIRST: "<<std::endl;
					for(int i=0;i<first.size();i++){
					std::cout<<first[i]<<" ";
					}
					std::cout<<" "<<std::endl;
						for(int u=1; u<validContigs.size(); u++){
							int index = contigIdmap[std::to_string(validContigs[u])];
							
							std::vector<std::string> second=getTranscript(Contig2Transcript[contigIdmap[std::to_string(validContigs[index])]]);				
							std::cout<<"SECOND: "<<std::endl;
							for(int i=0;i<second.size();i++){
							std::cout<<second[i]<<" ";
							}
						std::cout<<" "<<std::endl;
							std::sort(first.begin(), first.end());
							std::sort(second.begin(), second.end());
							std::set_intersection(first.begin(),first.end(),second.begin(),second.end(),back_inserter(first));			
						std::cout<<"Intersection is: "<<std::endl;	
						for(int i=0;i<first.size();i++){
							std::cout<<first[i]<<" ";
							}
						std::cout<<" "<<std::endl;						
						// Take intersection of first and second
						//and save it in the variable first 													
						}
					std::vector<std::string> temp1;
					std::set_difference(first.begin(), first.end(), transcripts.begin(), transcripts.end(), std::inserter(temp1, temp1.begin()));
					
					skipLength = (int)floor((contigInfo.find(paths[i])->second - n) / n);
					int insertValue = temp1.size() * skipLength;
					output.push_back(insertValue);
					/*auto checkOutput = output.find(validContigs);
					if (checkOutput != output.end()) {
						//cout << "in condition" << '\n';
						//cout << checkOutput->second << '\n';
						checkOutput->second = checkOutput->second + (1 + skipLength);
						//cout << checkOutput->second << '\n';
					}
					else {
						output.insert(pair <vector<int>, int>(validContigs, 1 + skipLength));
					}*/
					remaining = n;
					continue;
				}
				for (unsigned k = i + 1; k < paths.size(); k++) {
					remaining = remaining - contigInfo.find(paths[k])->second;
					validContigs.push_back(paths[k]);
					//vector<Positions> first = Contig2Transcript[contigIdMap[validContigs[0]]];
					
					if (remaining <= 0) {
						std::vector<std::string> first=getTranscript(Contig2Transcript[contigIdmap[std::to_string(validContigs[0])]]);
					std::cout<<"FIRST: "<<std::endl;
					for(int i=0;i<first.size();i++){
					std::cout<<first[i]<<" ";
					}
					std::cout<<" "<<std::endl;
						for(int u=1; u<validContigs.size(); u++){
							int index = contigIdmap[std::to_string(validContigs[u])];
							
							std::vector<std::string> second=getTranscript(Contig2Transcript[contigIdmap[std::to_string(validContigs[index])]]);				
							std::cout<<"SECOND: "<<std::endl;
							for(int i=0;i<second.size();i++){
							std::cout<<second[i]<<" ";
							}
						std::cout<<" "<<std::endl;
							std::sort(first.begin(), first.end());
							std::sort(second.begin(), second.end());
							std::set_intersection(first.begin(),first.end(),second.begin(),second.end(),back_inserter(first));			
						std::cout<<"Intersection is: "<<std::endl;	
						for(int i=0;i<first.size();i++){
							std::cout<<first[i]<<" ";
							}
						std::cout<<" "<<std::endl;						
						// Take intersection of first and second
						//and save it in the variable first 													
						}
						std::vector<std::string> temp1;
						std::set_difference(first.begin(), first.end(), transcripts.begin(), transcripts.end(), std::inserter(temp1, temp1.begin()));
						if (contigInfo.find(paths[i])->second <= abs(remaining)) {
							skipLength = contigInfo.find(paths[i])->second;
							/*auto checkOutput = output.find(validContigs);
							if (checkOutput != output.end()) {
								//cout << "in condition" << '\n';
								//cout << checkOutput->second << '\n';
								checkOutput->second = checkOutput->second + (1 + skipLength);
								//cout << checkOutput->second << '\n';
							}
							else {
								output.insert(pair <vector<int>, int>(validContigs, 1 + skipLength));
							}*/
							int insertValue = temp1.size() * skipLength;
							output.push_back(insertValue);
							remaining = n;
							break; //go to next contig in outer loop
						}
						else {
							skipLength = abs(remaining);
							int insertValue = temp1.size() * skipLength;
							output.push_back(insertValue);
							/*auto checkOutput = output.find(validContigs);
							if (checkOutput != output.end()) {
								//cout << "in condition" << '\n';
								//cout << checkOutput->second << '\n';
								checkOutput->second = checkOutput->second + (1 + skipLength);
								//cout << checkOutput->second << '\n';
							}
							else {
								output.insert(pair <vector<int>, int>(validContigs, 1 + skipLength));
							}*/
							remaining = n - contigInfo.find(paths[i])->second - abs(remaining);
							flag == 1;
							validContigs.push_back(paths[i]);
							break;
							//continue;
						}
					}
					else 
						remaining = n;
				}
			}
		transcripts.push_back(pathid);
		}
		
	}
	myfile.close();
	for(int n : output) {
		std::cout << n << "\n";
		outputFile << n << ',';
	}
	outputFile.close();
	//cout << output.size() << '\n';
	/*cout << "output is being written to the file" << "\n";
	map <std::vector<int>, int> ::iterator it2;
	for (it2 = output.begin(); it2 != output.end(); ++it2) {
		for (auto i = it2->first.begin(); i != it2->first.end(); ++i)
			outputFile << *i << ',';
		outputFile << it2->second << '\n';
	}
	outputFile.close();*/
}


