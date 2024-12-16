//
//  YZKSliderViewController.m
//  OpenGLESDemo
//
//  Created by ByteDance on 2024/12/13.
//

#import "YZKSliderViewController.h"
#import "YZKGLView.h"
#import "YZKRender.h"

@interface YZKSliderViewController ()
@property (nonatomic, strong) YZKGLView *glView;
@property (nonatomic, strong) UISlider *slider;
@end

@implementation YZKSliderViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = self.shaderTitle;
    
    self.slider = [[UISlider alloc]initWithFrame:CGRectMake(20, 110, self.view.frame.size.width - 40, 30)];
    _slider.value = 0;
    [_slider addTarget:self action:@selector(valueChanged:) forControlEvents:UIControlEventValueChanged];
    [self.view addSubview:self.slider];

    
    YZKGLView *view = [[YZKGLView alloc] initWithFrame:CGRectMake(10, 150, self.view.bounds.size.width-20, self.view.bounds.size.height-300)];
    [self.view addSubview:view];
    self.glView = view;
    
    NSString *renderClass = [NSString stringWithFormat:@"YZK%@Render", self.shaderTitle];
    Class class = NSClassFromString(renderClass);
    if (class) {
        YZKRender *render = [[class alloc] init];
        render.size = view.bounds.size;
        [render prepareProgramWithShader];
        [render renderWithContext:view.context];
        view.render = render;
    }
}

- (void)valueChanged:(UISlider *)slider
{
    [self.glView.render sliderValueChanged:slider.value];
}

- (void)dealloc {
    [self.glView.render stopRender];
}

@end
