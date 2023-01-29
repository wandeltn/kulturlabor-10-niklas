# Screen Order

```Mermaid
flowchart LR
    MainScreen --> FoodScreen
    MainScreen --> LightScreen
    MainScreen --> PlayScreen
    MainScreen --> MedicineScreen
    MainScreen --> PoopScreen
    MainScreen --> StatsScreen
    MainScreen --> DiciplineScreen
    MainScreen --> SettingsScreen

    SettingsScreen --> WifiSettingsScreen
    WifiSettingsScreen --> WifiModeScreen
    WifiSettingsScreen --> WifiConnectScreen
```
