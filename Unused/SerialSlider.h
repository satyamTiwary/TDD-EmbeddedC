void process_command(const short input) {
  if (input == 0) {
    return;
  }

  switch (input) {
  case COMMAND_MOVE_OUT:
    if (not_in_this_state('f', "Already in the Outward most Position")) {
      motor_direction = OUTWARDS;
      motor_state = MOVE;
      // state::instrumentState = InstrumentState::SLI
    }
    break;
  case COMMAND_MOVE_IN:
    if (find_state() == 'b') {
#ifdef DEBUG
      Serial.println(
          "Already in the BacInward most Position. Collision case avoided.");
#endif
      break;
    } else {
      motor_direction = INWARDS;
      motor_state = MOVE;
      break;
    }
  case 3:
    debug(find_state());
    motor_state = STOP;
    break;
  case 4:
    motor_state = IDLE;
    break;
  case 5:
    debug(find_state());
    break;
  default:
    error("");
    break;
  }

#ifdef DEBUG
  print_state();
#endif
}
