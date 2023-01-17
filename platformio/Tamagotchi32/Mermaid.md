# Mermaid

::: mermaid
stateDiagram-v2
    [*] --> setup
    setup --> loop
    loop --> is_screen_on

    state setup {
        Neopixel_on --> Display_on
        Display_on --> Enable_buttons
        Enable_buttons --> Display.dim
        Display.dim --> Activate_MainScreen
        Activate_MainScreen --> Begin_Tamastatus
    }

    state loop {
        is_screen_on --> screen_on : true
        is_screen_on --> screen_off : false 
    }

    state screen_on {
        Update_Screen --> is_schedule_rerender
        is_schedule_rerender --> yes_schedule_rerender : true
        is_schedule_rerender --> not_schedule_rerender : false
    }

    state screen_off {
        Check_timers --> Disable_Serial
        Disable_Serial --> shutdown
    }

    state shutdown {
        Disable_TamaStatus --> Enable_deepsleepWakeup
        Enable_deepsleepWakeup --> Enable_deepsleep
    }

    state not_schedule_rerender {
        test
    }

    state yes_schedule_rerender {
        test3
    }
:::
