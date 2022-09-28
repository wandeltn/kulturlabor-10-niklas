# States

## Pooping

### `poop_on_screen: int`

> represents the amount of times the player has not cleaned the poop off the screen.
>
> If thes number exceeds the allowed amount the tama may get sick.
> The chance of sickness increases with more poop exceeding the limit further
>
> If a critical threshold is reached, the tama will get a care error.
> If the problem persists even further, the tama will die.

## Hunger

### `hunger_value: int`

> Represents the hunger of the tama. The value range usually is 0-5.
>
> The bar can be refilled by feeding the tama with burgers or a equivalent food.
>
> If the bar reaches 0 this will add a care mistake. If the problem persists even further, the tama will die.

### `time_last_eaten: int`

> marks the time that the tama has last eaten.
>
> This is mostly important to determine the next time it will have to eat

## Happiness

### `happiness_value: int`

> represents the happiness value of the tama in a range of 0-5.
>
> It will also add care errors if not taken care of by feeding the tama cake of an equivalent food source
>
> This is important to determine the evolutions of the tama along with the healthyness, training and care errors

## Healthyness

### `sickness_value: int`

> Represents the healthiness of the tama, this is affected by the poop, happiness and hunger values.
>
> If not taken care of it will add care errors.
> Improve by giving medicine of vaccine.
>
> If not taken care of for a specific amount of time, may result in death

### `unhealthy_time: int`

> Represents the time since the tama has gotten ill
> and is used to determine the concequences of illness

## Training

### `training_status: ?`

> will be used to save the training status of the tama used to determine the amount of misbehauvior.
>
> Improving this value will result in better evolutions and easier proceeding of the game

## Care errors

### `care_errors: int`

> Represents the number of times the user has disregarded the life of the tama.
>
> The value will determine the further evotlutions of the tama
