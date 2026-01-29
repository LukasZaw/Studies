import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow.keras import layers
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_absolute_error

df = pd.read_csv("history_bulk.csv")
df = df.dropna(subset=["temp"])
temp = df["temp"].astype(float).values

scaler = StandardScaler()
temp_scaled = scaler.fit_transform(temp.reshape(-1, 1)).flatten()

sequence_length = 10
X, y = [], []
for i in range(len(temp_scaled) - sequence_length):
    X.append(temp_scaled[i:i + sequence_length])
    y.append(temp_scaled[i + sequence_length])

X = np.array(X)
y = np.array(y)

# Train
split_ratio = 0.8
split_index = int(split_ratio * len(X))
X_train, X_test = X[:split_index], X[split_index:]
y_train, y_test = y[:split_index], y[split_index:]


model = tf.keras.Sequential([
    layers.Input(shape=(sequence_length,)),
    layers.Dense(64, activation='relu'),
    layers.Dense(1)
])
model.compile(optimizer='adam', loss='mean_squared_error')

# Train
history = model.fit(X_train, y_train, epochs=100, batch_size=32,
                    validation_data=(X_test, y_test), verbose=0)

# Predict
y_pred_scaled = model.predict(X_test, verbose=0).flatten()

y_test_k = scaler.inverse_transform(y_test.reshape(-1, 1)).flatten()
y_pred_k = scaler.inverse_transform(y_pred_scaled.reshape(-1, 1)).flatten()

y_test_c = y_test_k - 273.15
y_pred_c = y_pred_k - 273.15

# MAE
mae_c = mean_absolute_error(y_test_c, y_pred_c)
print(f"MAE (°C): {mae_c:.3f}")

plt.figure(figsize=(8, 4))
plt.plot(history.history["loss"], label="train")
plt.plot(history.history.get("val_loss", []), label="val")
plt.xlabel("Epoka")
plt.ylabel("MSE")
plt.legend()
plt.title("Traning i Strata")
plt.show()

# Plot
plt.figure(figsize=(8, 6))
plt.plot(y_test_c, label="Rzeczywista (następna godzina)")
plt.plot(y_pred_c, label="Przewidywana")
plt.xlabel("Próbka")
plt.ylabel("Temperatura (°C)")
plt.legend()
plt.title("Temperatura Rzeczywista vs Przewidywana (°C)")
plt.show()
