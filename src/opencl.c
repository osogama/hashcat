/**
 * Authors.....: Jens Steube <jens.steube@gmail.com>
 *               Gabriele Gristina <matrix@hashcat.net>
 *
 * License.....: MIT
 */

#include "common.h"
#include "types_int.h"
#include "types.h"
#include "memory.h"
#include "logging.h"
#include "ext_OpenCL.h"
#include "timer.h"
#include "opencl.h"

uint setup_opencl_platforms_filter (char *opencl_platforms)
{
  uint opencl_platforms_filter = 0;

  if (opencl_platforms)
  {
    char *platforms = mystrdup (opencl_platforms);

    char *next = strtok (platforms, ",");

    do
    {
      int platform = atoi (next);

      if (platform < 1 || platform > 32)
      {
        log_error ("ERROR: Invalid OpenCL platform %u specified", platform);

        exit (-1);
      }

      opencl_platforms_filter |= 1u << (platform - 1);

    } while ((next = strtok (NULL, ",")) != NULL);

    myfree (platforms);
  }
  else
  {
    opencl_platforms_filter = -1u;
  }

  return opencl_platforms_filter;
}

u32 setup_devices_filter (char *opencl_devices)
{
  u32 devices_filter = 0;

  if (opencl_devices)
  {
    char *devices = mystrdup (opencl_devices);

    char *next = strtok (devices, ",");

    do
    {
      int device_id = atoi (next);

      if (device_id < 1 || device_id > 32)
      {
        log_error ("ERROR: Invalid device_id %u specified", device_id);

        exit (-1);
      }

      devices_filter |= 1u << (device_id - 1);

    } while ((next = strtok (NULL, ",")) != NULL);

    myfree (devices);
  }
  else
  {
    devices_filter = -1u;
  }

  return devices_filter;
}

cl_device_type setup_device_types_filter (char *opencl_device_types)
{
  cl_device_type device_types_filter = 0;

  if (opencl_device_types)
  {
    char *device_types = mystrdup (opencl_device_types);

    char *next = strtok (device_types, ",");

    do
    {
      int device_type = atoi (next);

      if (device_type < 1 || device_type > 3)
      {
        log_error ("ERROR: Invalid device_type %u specified", device_type);

        exit (-1);
      }

      device_types_filter |= 1u << device_type;

    } while ((next = strtok (NULL, ",")) != NULL);

    myfree (device_types);
  }
  else
  {
    // Do not use CPU by default, this often reduces GPU performance because
    // the CPU is too busy to handle GPU synchronization

    device_types_filter = CL_DEVICE_TYPE_ALL & ~CL_DEVICE_TYPE_CPU;
  }

  return device_types_filter;
}