import helpers
import time
import ximu3


def print_progress(progress):
    print(
        ", ".join(
            [
                ximu3.file_converter_status_to_string(progress.status),
                "{:.1f}%".format(progress.percentage),
                f"{progress.bytes_processed} of {progress.file_size} bytes",
            ]
        )
    )
    # print(progress.to_string())  # alternative to above


def callback(progress):
    print_progress(progress)


destination = "C:/"
source = "C:/file.ximu3"

if helpers.ask_question("Use async implementation?"):
    _ = ximu3.FileConverter(destination, source, callback)
    time.sleep(60)
else:
    print_progress(ximu3.FileConverter.convert(destination, source))
