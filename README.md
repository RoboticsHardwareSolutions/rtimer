# rtimer

smal wrapper on timer in STM32    
used TIM7
supported MCU : STM32G474xx, 

```

typedef enum {
    once,
    periodically,
} rtimer_type;

typedef struct {
    rtimer_type type;
    uint32_t elapsed_time;
    uint32_t period;
    bool activated;
    void (*callback)(void);
    struct rtimer_t *next;
} rtimer;


/**
 * created timer with one of choosen type
 * periodically or once shot
 * return false if hardware timer not started
 */
bool rtimer_create(rtimer *instance, rtimer_type type);

/**
 * setup period of work timer and register callback function
 * return false if not coorect arg
 */
bool rtimer_setup(rtimer *instance, uint32_t period_ms, void *cb);

/**
 * deactivated timer  
 */
void rtimer_delete(rtimer *instance);

```


 EXAMPLE: 
 
 ```
rtimer timer1 = {0};  //init  timer1
rtimer timer2 = {0};  //init  timer2

rtimer_create(&timer1, periodically); //create periodically timer1
rtimer_create(&timer2, once); // type one shot timer2

rtimer_setup(&timer1, 300, led_red_toggle); // setup period in ms and register callback fnction
rtimer_setup(&timer2, 1000, led_green_toggle); // setup period in ms and register callback fnction

 ```
