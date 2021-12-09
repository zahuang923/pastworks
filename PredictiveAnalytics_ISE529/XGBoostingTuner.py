import numpy as np
import pandas as pd
from xgboost import XGBClassifier
from sklearn.metrics import accuracy_score
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import StratifiedKFold


class Tuner:
    def __init__(self):
        self.kfold_splits = 10
        self.params = dict()
        self.result = pd.DataFrame()

    def Tune(self, x, y, scoring_method='neg_log_loss'):
        model = XGBClassifier()
        kfold = StratifiedKFold(
            n_splits=self.kfold_splits, shuffle=True, random_state=1)
        grid_search = GridSearchCV(
            model, param_grid=self.params, scoring=scoring_method, return_train_score=True, cv=kfold)
        grid_result = grid_search.fit(x, y)

        # result
        means = grid_result.cv_results_['mean_test_score']
        params = grid_result.cv_results_['params']
        self.result = pd.DataFrame()
        self.result['params'] = params
        self.result['mean test score'] = means
        return grid_result.best_params_
