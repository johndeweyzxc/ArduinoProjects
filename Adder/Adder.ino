// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// String to print
const char msg[] = "Barkadeer brig Arr booty rum.";

// Task handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

// Task: print to Serial terminal with lower priority
void startTask1(void *parameter) {

  // Count number of characters in String
  int msg_len = strlen(msg);

  // Print string to terminal
  while (1) {
    Serial.println();
    for (int i = 0; i < msg_len; i++) {
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000 / portTick_PERIOD_MS);
  }
}

void startTask2(void *parameters) {
  while (1) {
    Serial.print("*");
    vTaskDelay(100 / portTick_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(300);
  
  vTaskDelay(1000 / portTick_PERIOD_MS);
  Serial.println();
  Serial.println("----FreeRTOS Task Demo----");
  
  // Print self priority
  Serial.print("Setup and loop task running on core");
  Serial.print(xPortGetCoreID());
  Serial.print(" with priority ");
  Serial.println(uxTaskPriorityGet(NULL));

  // Task to run forever
  xTaskCreatePinnedToCore( 
    startTask1,
    "Task 1",
    1024,
    NULL,
    1,
    &task_1,
    app_cpu
  );

  // Task to run once with higher priority
  xTaskCreatePinnedToCore( 
    startTask2,
    "Task 2",
    1024,
    NULL,
    2,
    &task_2,
    app_cpu
  );
}

void loop() {
  // Suspend the higher priority task for some intervals
  for (int i = 0; i < 3; i ++) {
    vTaskSuspend(task_2);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    vTaskResume(task_2);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }

  // Delete lower priority task
  if (task_1 != NULL) {
    vTaskDelete(task_1);
    task_1 = NULL;
  }
}