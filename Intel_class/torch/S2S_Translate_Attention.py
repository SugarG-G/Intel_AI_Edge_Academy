import torch
import torch.nn as nn
import numpy as np
import random
from sentance_preprocess import read_language
from langchain_community.embeddings import HuggingFaceEmbeddings
from transformers import AutoTokenizer, AutoModel
from torch.utils.data import TensorDataset, DataLoader

class Encoder(nn.Module):
    def __init__(self,
        # moduleSelect = int,
        vocab_size : int,
        embed_size : int,
        hidden_size ,
        dropout = 0.1,
    ):
        super().__init__()
        self.hidden_size = hidden_size
        self.embedding = nn.Embedding(vocab_size, embed_size, padding_idx=tokenizer.pad_token_id)
        self.GRU = nn.GRU(embed_size, hidden_size, batch_first=True)

        def forward(self, input):
            embedded = self.embedding(input)
            output, hidden = self.GRU(embedded)
            return output, hidden

class Attention(nn.Module):
    def __init__(self, hidden_size):
        super().__init__()
        self.hidden_size = hidden_size
        self.softmax = nn.Softmax(2)
        # decoder input으로는 문자가 들어오니, hidden size (wordvec 을 알고있어야 함)