# import numpy as np
#
#
# class QLearning(object):
#     def __init__(self, state_dim, action_dim, cfg):
#         self.action_dim = action_dim  # dimension of acgtion
#         self.lr = cfg.lr  # learning rate
#         self.gamma = cfg.gamma # 衰减系数
#         self.epsilon = 0
#         self.sample_count = 0
#         self.Q_table = np.zeros((state_dim, action_dim))  # Q表格
#
#     def choose_action(self, state):
#         ####################### 智能体的决策函数，需要完成Q表格方法（需要完成）#######################
#         self.sample_count += 1
#         action = np.random.choice(self.action_dim)  #随机探索选取一个动作
#         return action
#
#     def update(self, state, action, reward, next_state, done):
#         ############################ Q表格的更新方法（需要完成）##################################
#         pass
#
#     def save(self, path):
#         np.save(path + "Q_table.npy", self.Q_table)
#
#     def load(self, path):
#         self.Q_table = np.load(path + "Q_table.npy")
import numpy as np
import random

class QLearning(object):
    def __init__(self, state_dim, action_dim, cfg):
        self.action_dim = action_dim  # dimension of acgtion
        self.lr = cfg.lr  # learning rate
        self.gamma = cfg.gamma # 衰减系数
        self.epsilon = 0
        self.sample_count = 0
        self.Q_table = np.zeros((state_dim, action_dim))  # Q表格

    def choose_action(self, state):
        if random.random() < 0.01:
            return np.random.randint(4)
        else:
            action_max = np.max(self.Q_table[state, :])
            choice_action = np.where(action_max == self.Q_table[state, :])[0]
            return np.random.choice(choice_action)

    def update(self, state, action, reward, next_state, done):
        Q_ = self.Q_table[state][action]
        if done:
            target_Q = 10000
        else:
            target_Q = reward + self.gamma * np.max(self.Q_table[next_state, :])  # Q_learning
        self.Q_table[state][action] += self.lr * (target_Q - Q_)

    def predict(self, state):
        action = np.argmax(self.Q_table[state])
        return action

    def save(self, path):
        np.save(path + "Q_table.npy", self.Q_table)

    def load(self, path):
        self.Q_table = np.load(path + "Q_table.npy")
