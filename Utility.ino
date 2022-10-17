/*
 *	UOS Arduino Firmware
 *	See <https://wiki.nulltek.xyz/projects/uos/>
 *
 *	Copyright © 2022 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/UOS-Arduino/>
 *
 *	Helper algorithms and functions
 */

bool exists_in_sorted_array(uint8_t value, const uint8_t arr[],
                            uint8_t arr_len) {
  uint8_t low_range = 0;
  uint8_t high_range = arr_len - 1;
  uint8_t index = uint8_t(high_range / 2);  // start in the middle
  for (uint8_t i = 0; i < arr_len; i++) {
    if (arr[index] == value) {
      return true;
    } else if (value < arr[index]) {
      high_range = index - 1;
    } else {
      low_range = index + 1;
    }
    uint8_t index_prior = index;
    index = uint8_t((high_range + low_range) / 2);
    if (index_prior == index) {
      return false;  // Value doesn't exist
    }
  }
  return false;
}
