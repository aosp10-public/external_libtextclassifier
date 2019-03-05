/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.google.android.textclassifier.utils.calendar;

import static com.google.common.truth.Truth.assertThat;

import com.google.thirdparty.robolectric.GoogleRobolectricTestRunner;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

/** This is just a launcher of the tests because we need a valid JNIEnv in the C++ test. */
@RunWith(GoogleRobolectricTestRunner.class)
public class CalendarJavaIcuLocalTest {

  @Before
  public void setUp() throws Exception {
    System.loadLibrary("calendar-javaicu_test-lib");
  }

  private native boolean testsMain();

  @Test
  public void testNative() {
    assertThat(testsMain()).isTrue();
  }
}
