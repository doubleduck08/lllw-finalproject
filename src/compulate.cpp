void Pattern::compulate(Example ori1, Example ori2)
{
  int compuRatio = colorCompsNum / 10 + 1;
  
  bool tmp[colorCompsNum];
  memset(tmp, 0, sizeof(bool) * colorCompsNum);
  
  for(int i=0; i < compuRatio; ++i){
    tmp[i] = ori1.colorGene[i];
    ori1.colorGene[i] = ori2.colorGene[i];
    ori2.colorGene[i] = tmp[i];
  }
  
}

void Pattern::findBest()
{
  Example candidate[CandNum];
  double score[CandNum];
  double sum = 0;
  double ratio[CandNum] = {0.0, 0.0, 0.0, 0.0};
  vector<Example> seleteExp;

  for(int i=0; i < CandNum; ++i){
    gen_Gene(candidate[i]);
    score[i] = getScore(candidate[i]);
    sum += (1 / score[i]);
  }
  
  for(int i=0; i < CandNum; ++i){
    ratio[i] = (score[i] / sum);
    if(i > 0)
      ratio[i] += ratio[i-1];
  }

  for(int i=0; i < CandNum; ++i){
    seleteExp.push_back(candidate[drawExample(candidate, ration)])
  }

  //compulate
  for(int i=0; i < CandNum / 2; i+=2){
    compulate(seleteExp[i], seleteExp[i+1])
  }

  //mutation
  mutation(seleteExp);

  return seleteExp;
}

int Pattern::drawExample(Example* candidate, const double* ratio){
  double randNum = srand(time(0)) / RAND_MAX;
  int selete=0;
  for(; flag < CandNum; ++flag){
    if(randNum < ratio[i])
      break;
  }
  return selete;
}

