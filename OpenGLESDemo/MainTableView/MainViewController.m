//
//  MainViewController.m
//  OpenGLESDemo
//
//

#import "MainViewController.h"
#import "YZKTitleTableViewCell.h"
#import "YZKViewController.h"
#import "YZKSliderViewController.h"

@interface MainViewController () <UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) NSArray *dataArray;

@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = @"Main";

    UITableView *tableView = [[UITableView alloc] initWithFrame:self.view.bounds];
    tableView.delegate = self;
    tableView.dataSource = self;
    [tableView registerClass:[YZKTitleTableViewCell class] forCellReuseIdentifier:@"YZKTitleTableViewCell"];
    [self.view addSubview:tableView];
    
    [self configDataArray];
}

- (void)configDataArray {
    self.dataArray = @[
        @"Normal",
        @"NormalEBO",
        @"UniformColor",
        @"Texture",
        @"LUT",
        @"Gray",
        @"ReverseColor",
        @"Slider_Contrast",
        @"Slider_Saturation",
        @"Slider_Sharpen",
//        @"Slider_",
//        @"Slider_",
//        @"Slider_",
//        @"Slider_",
    ];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    YZKTitleTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"YZKTitleTableViewCell" forIndexPath:indexPath];
    cell.title = self.dataArray[indexPath.row];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    NSString *dataString = self.dataArray[indexPath.row];
    NSRange range = [dataString rangeOfString:@"Slider_"];
    if (range.location != NSNotFound) {
        NSString *shaderName = [dataString substringFromIndex:NSMaxRange(range)];
        YZKSliderViewController *vc = [[YZKSliderViewController alloc] init];
        vc.shaderTitle = shaderName;
        [self.navigationController pushViewController:vc animated:YES];
    } else {
        YZKViewController *vc = [[YZKViewController alloc] init];
        vc.shaderTitle = dataString;
        [self.navigationController pushViewController:vc animated:YES];
    }
}


@end
